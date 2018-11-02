#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<fstream>


using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y);           //function to set the cursor
void SetColor(int ForgC);           //function to set the color
void box();                         //function to display the box
void admin();                       //function for admin menu in the main menu
void book_ticket();                 //function for booking tickets menu
void seats(int cd);

class show                          //class having the details of all the movies
{
public:
    char movie_name[50];
    int mv_cd,ticket_cost,tno_s,s_res;
    int seat[11][20];

    void add()
    {
        system("cls");              //add the given show to the file
        cout<<"ENTER THE DETAILS - \n";
        cout<<"MOVIE NAME : ";
        cin>>movie_name;
        cout<<"MOVIE CODE : ";
        cin>>mv_cd;
        cout<<"COST OF TICKET : ";
        cin>>ticket_cost;
        tno_s=220;
        s_res=0;
        for(int i=0;i<11;i++)
            for(int j=0;j<20;j++)
                seat[i][j]=0;
        // now write it in file show.dat
        cout<<this->movie_name;
        fstream f1;
        f1.open("movie.dat",ios::app|ios::binary);
        f1.write((char*)this,sizeof(show));
        f1.close();
        getch();
    }
    void get_det(int m_cd)
    {
        //system("cls");
        //cout<<"get details";
        fstream f1;
        f1.open("movie.dat",ios::in|ios::binary);
        f1.seekg((sizeof(show)*(m_cd-1)),ios::beg);         //jump to the required movie record
        f1.read((char*)this,sizeof(show));
        f1.close();
    }
    void rem()                      //to be made
    {
        system("cls");              //remove the asked show from the file
        cout<<"remove";
        getch();
    }
    void reset()                //to be made
    {
        system("cls");
        cout<<"reset";       //reset the seat array to 0
        getch();
    }

};

class customer
{
private:

public:
    char c_name[50];
    char phn_no[10];

};

class ticket
{
public:
    show s1;
    int show_cd;
    int tic_id;
    customer c1;
    int n_o_t;
    int chairs[2][10];

public:
    void book()                 //working on right now
    {
        cout<<"hello book your ticket";
        getch();
        system("cls");
        seats(show_cd);             //displays the theature and return the control
        //now get the details of the booked tickets in the 2-d array by mov function
        this->mov();
                        //now rewrite the edited files back
                        //append the record in tickets.dat
                        //and overwrite the record in show.dat
        fstream f1;
        //f1.open("tickets.dat",ios::app||ios::binary);

        getch();

    }
    void mov()             //movement of the cursor and book the required seats
    {

        int arr[11][20],i=0,j=0,ctr=0;
        int count=1,flag=0,x=0,y=0;
        char a;

        int k=0;
        while(count<=this->n_o_t)                                     // no of tickets booked is less than no of tickets req.
        {
            gotoxy(0,0);
            printf("   ");
            a=getch();              //takes input for movement of cursor
            if(flag!=1)             //if seat is not reserved in the previous iteration change to seat to appropriate color
            {
                gotoxy(x,y);
                if(this->s1.seat[j][i]==0)        //if unreserved
                    SetColor(15);           //white
                else if(arr[j][i]==1)       //if already reserved recently reserved
                    SetColor(12);           //red
                else                        //if already reserved
                    SetColor(9);            //blue
                printf("|%2d|",i+1);
            }
            switch(a)
            {
                case 'a':               //moves the cursor left
                case 'A':
                    if(i>0)             //so that cursor doesn't move out of matrice
                    {
                        i--;
                        flag=0;
                    }
                    break;
                case 'd':               //moves the cursor right
                case 'D':
                    if(i<19)            //so that cursor doesn't move out of matrice
                    {
                        i++;
                        flag=0;
                    }
                    break;
                case 'w':               //moves the cursor up
                case 'W':
                    if(j>0)             //so that cursor doesn't move out of the matrice
                    {
                        j--;
                        flag=0;
                    }
                    break;
                case 's':               //moves the cursor down
                case 'S':
                    if(j<10)            //so that cursor doesn't move out of the matrice
                    {
                        j++;
                        flag=0;
                    }
                    break;
                case ' ':               //for selection of the seat
                    if(this->s1.seat[j][i]==0)//check if the seat is already reserved
                    {
                        count++;        //increment no. of seats booked
                        flag=1;
                        this->s1.seat[j][i]=1;//change status of seat to booked
                        arr[j][i]=1;
                        this->chairs[0][k]=j;//store the seat no in details
                        this->chairs[1][k]=i;
                        k++;
                        this->s1.s_res++;      //increase the no. of seats reserved
                    }
                    break;
                default :;
            }
            x=29+(i*5);                 //position the x co-ordinate
            y=4+(j*2);                  //position the y co-ordinate
            if(i>=10)
            {
                x=x+7;
            }
            gotoxy(x,y);                //move the cursor to the right position
            SetColor(12);
            printf("|%2d|",i+1);        //display the seat on which the cursor is present
        }
        gotoxy(40,40);                          //moves to pointer to the position out of the layout
    }
    void get_det()
    {
        char ans='N';
        int check=1,i=0;
        while(ans=='N'||ans=='n')              //accepts details after checking all the details
        {
            {                                  //clear the input area for the new input
                gotoxy(73,20);cout<<"                               ";
                gotoxy(73,21);cout<<"                               ";
                gotoxy(73,22);cout<<"                               ";
                gotoxy(73,23);cout<<"                               ";
            }
            fflush(stdin);
            gotoxy(40,18);cout<<"ENTER THE FOLLOWING DETAILS :";
            gotoxy(40,20);cout<<"NAME                        :";
            gotoxy(40,21);cout<<"PHONE NUMBER                :";
            gotoxy(40,22);cout<<"MOVIE CODE                  :";
            gotoxy(40,23);cout<<"NUMBER OF TICKET            :";

            gotoxy(73,20);gets(this->c1.c_name);   //accepts name
            for(i=0;i<strlen(this->c1.c_name);i++) //change the case of each letter to upper
            {
                this->c1.c_name[i]=toupper(this->c1.c_name[i]);
            }

            while(1)                  //accepts the phn no. & check if its 10-digits
            {
                gotoxy(73,21);gets(this->c1.phn_no);
                if(strlen(this->c1.phn_no)==10)
                {
                    gotoxy(90,21);cout<<"                               ";
                    break;
                }
                gotoxy(73,21);cout<<"                   ";
                gotoxy(90,21);cout<<"PLEASE ENTER A 10-DIGIT NUMBER";
            }

            while(1)                 //accepts the movie code b/w 1&5
            {
                gotoxy(73,22);cin>>this->show_cd;
                if(this->show_cd==1||this->show_cd==2||this->show_cd==3||this->show_cd==4||this->show_cd==5)
                {
                    gotoxy(95,22);cout<<"                                          ";
                    break;
                }
                gotoxy(73,22);cout<<"      ";
                gotoxy(95,22);cout<<"PLEASE INPUT A VALID MOVIE CODE";
            }

            while(1)                 //accepts no. tickets to be booked not more the 10
            {
                gotoxy(73,23);cin>>this->n_o_t;
                if(this->n_o_t<=10&&this->n_o_t>0)
                {
                    gotoxy(95,23);cout<<"                                                   ";
                    break;
                }
                gotoxy(73,23);cout<<"      ";
                gotoxy(95,23);cout<<"YOU CAN NOT BOOK MORE THAN 10 TICKETS AT A TIME";
            }

            gotoxy(40,18);printf("PLEASE CONFIRM YOUR DETAIS  :");      //confirms the details
            gotoxy(73,20);puts(this->c1.c_name);                              //displays all the details accepted
            gotoxy(73,21);puts(this->c1.phn_no);
            gotoxy(73,22);cout<<this->show_cd;
            gotoxy(73,23);cout<<this->n_o_t;
            fflush(stdin);
            gotoxy(40,25);cout<<"ARE YOUR DETAILS CORRECT (Y/N) : ";
            cin>>ans;
            ans=toupper(ans);

            this->s1.get_det(this->show_cd);
        }
    }

    print();
    cancel();
    get();
};

int main()
{
    char opt;
    int ch=1;
    while(ch==1)
    {
        system("cls");
        SetColor(15);
        box();
        gotoxy(72,3) ;cout<<"WELCOME TO SHOW BOX";
        gotoxy(71,4) ;cout<<"---------------------";
        gotoxy(77,6) ;cout<<"MAIN MENU";
        gotoxy(50,10);cout<<"BOOK TICKETS";
        gotoxy(50,11);cout<<"CANCEL TICKETS";
        gotoxy(50,12);cout<<"PRINT TICKETS";
        gotoxy(50,13);cout<<"ADMINISTRATION";
        gotoxy(50,14);cout<<"EXIT";

        gotoxy(100,10);cout<<"1";
        gotoxy(100,11);cout<<"2";
        gotoxy(100,12);cout<<"3";
        gotoxy(100,13);cout<<"4";
        gotoxy(100,14);cout<<"0";

        gotoxy(62,17);cout<<"ENTER YOUR OPTION :         ";
        scanf("%c",&opt);

        switch(opt)
        {
            case '1': book_ticket();
                break;
          //  case '2': canc_tics();
          //      break;
          //  case '3': check_det();
          //      break;
            case '4': admin();
                break;
            case '0': ch=0;
                break;
            default : //wrong input
                break;
         }

    }
    return 0;
}

void gotoxy(int x,int y)                    //to position the pointer
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC)                    //to set color
{
     WORD wColor;
                          //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

                           //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void box()                                  //displays the outer box
{
    int i=0;
    gotoxy(16,1); printf("%c",201);         // upper horizontal
    for(i=0;i<130;i++)
        printf("%c",205);
    printf("%c",187);

    gotoxy(16,30);printf("%c",200);         //lower horizontal
    for(i=0;i<130;i++)
        printf("%c",205);
    printf("%c",188);

    for(i=1;i<29;i++)                       //vertical lines
    {
        gotoxy(16,1+i); printf("%c",186);
        gotoxy(147,1+i);printf("%c",186);
    }
}

void admin()
{
    char opt;
    int ch=1;
    show s1;
    while(ch==1)
    {
        system("cls");
        SetColor(15);
        box();
        gotoxy(72,3) ;cout<<"HELLO ADMIN";
        gotoxy(71,4) ;cout<<"-------------";
        gotoxy(72,6) ;cout<<"ADMIN MENU";
        gotoxy(50,10);cout<<"ADD SHOW";
        gotoxy(50,11);cout<<"REMOVE SHOW";
        gotoxy(50,12);cout<<"RESET SHOW";
        gotoxy(50,13);cout<<"VIEW SHOW DETAILS";
        gotoxy(50,14);cout<<"EXIT";

        gotoxy(100,10);cout<<"1";
        gotoxy(100,11);cout<<"2";
        gotoxy(100,12);cout<<"3";
        gotoxy(100,13);cout<<"4";
        gotoxy(100,14);cout<<"0";

        gotoxy(62,17);cout<<"ENTER YOUR OPTION :         ";
        scanf("%c",&opt);
        switch(opt)
        {
            case '1': s1.add();
                break;
            case '2': s1.rem();
                break;
            case '3': s1.reset();
                break;
            case '4': system("cls");            //view details
                      for(int i=1;i<6;i++)
                      {
                        s1.get_det(i);
                        cout<<s1.movie_name<<s1.mv_cd<<s1.ticket_cost<<endl;
                      }
                      getch();
                break;
            case '0': ch=0;
                break;
            default : //wrong input
                break;
         }

    }

}

void book_ticket()
{
    {    //movie list showcase
        system("cls");
        box();
        show s1;                                  //display the outer box
        gotoxy(72,3);cout<<"WELCOME TO SHOW BOX";
        gotoxy(71,4);cout<<"---------------------";
        gotoxy(40,7);cout<<"MOVIE NAME";
        gotoxy(60,7);cout<<"COST OF TICKET";
        gotoxy(85,7);cout<<"MOVIE CODE";
        gotoxy(105,7);cout<<"NO. OF SEATS LEFT";
        for(int i=1;i<=5;i++)
        {
            s1.get_det(i);
            gotoxy(40,9+i);cout<<s1.movie_name;
            gotoxy(60,9+i);cout<<s1.ticket_cost;
            gotoxy(85,9+i);cout<<s1.mv_cd;
            gotoxy(105,9+i);cout<<(s1.tno_s-s1.s_res);
        }
    }

    ticket t1;
    t1.get_det();           //get the details of the tickets,customer

            //initialize seats(chairs),ticket id(tic_id)
    cout<<t1.s1.movie_name;
    t1.book();                  //go to the booking theature and select the wanted seats and get the selected seats
    //cout<<t1.s1.movie_name;


    getch();
}

void seats(int cd)           //displays the seating arrangement and return nothing to the called place
{
    system("cls");

    int i=0,j=0,z=0,x;
    int seats_a[11][20];
    char a;

    show s1;
    s1.get_det(cd);                                    // get the details of the desired movie

    box();                                             //displays border

    for(j=0;j<11;j++)                                  //displays the seats booked in blue and empty in white
    {
        gotoxy(25,4+(2*j));
        printf("%c - ",(j+65));
        for(i=0;i<20;i++)
        {
            if(s1.seat[j][i]==0)            //unreserved seats
            {
                SetColor(15);               //white
            }
            else if(s1.seat[j][i]==1)       //reserved seats
            {
                SetColor(9);                //blue
            }
            printf("|%2d| ",i+1);
            if(i==9)
            {
                SetColor(15);
                printf("%c -- %c ",j+65,j+65);
            }
        }
        SetColor(15);
        printf("- %c\n\n",j+65);
    }
    gotoxy(18,3);  SetColor(12);printf("|EXIT|");
    gotoxy(18,25); SetColor(12);printf("|EXIT|");
    gotoxy(140,3); SetColor(12);printf("|EXIT|");
    gotoxy(140,25);SetColor(12);printf("|EXIT|");
    gotoxy(68,27); SetColor(15);printf("<---- SCREEN THIS SIDE ---->");
    gotoxy(60,29);              printf("MOVIE CODE : %d",s1.mv_cd);
    gotoxy(87,29);              printf("MOVIE NAME : %s",s1.movie_name);

//-----------------displays controls to book seats---------------------
    gotoxy(28,34);printf("PRESS->  A: TO MOVE LEFT    D: TO MOVE RIGHT   W: TO MOVE UP");
                  printf("   S: TO MOVE DOWN   SPACEBAR: TO SELECT THE SEAT");

    gotoxy(25,32);printf("%c",218);             //border for the controls
    for(i=0;i<113;i++)
        {gotoxy(26+i,32);printf("%c",196);}
    gotoxy(138,32);printf("%c",191);
    for(i=0;i<3;i++)
        {gotoxy(25,33+i); printf("%c",179);
         gotoxy(138,33+i);printf("%c",179);}
    for(i=0;i<113;i++)
        {gotoxy(26+i,36);printf("%c",196);}
    gotoxy(138,36);printf("%c",217);
    gotoxy(25,36); printf("%c",192);
//----------------------------------------------------------------
    //returns to the function called
}

