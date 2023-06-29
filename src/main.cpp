#include <bits/stdc++.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <windows.h>

using namespace std;

struct point
{
	int x,y;
};
void usleepNew(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
point genNewPoint();
void printString(string);
void check(point* , point , int , point& );
bool readFile(string, int& , int & , point &, point & , int &, point* &, int & , int &);
void save(int , int  ,point , point , point*, int, int , int);
void showShape();
void menu(int & , int & , point & , point & , int &, point* & ,int & , int &);
void run();
int main()
{
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
    run();
}
void printString(string n)
{
    for(int i =0 ; i <n.size() ; i++ )
    {
        cout<<n[i];
        if(n[i]=='.')
        {
            sleep(2);
        }else
            usleepNew(60000);
    }
}
point genNewPoint()
{
	point p;
	p.x=1+rand()%15;
	p.y=1+rand()%15;
	return p;
}

void check(point* arr , point head , int size , point &p1)
{
	while(1)
	{
		if(head.x == p1.x && head.y == p1.y)
		{
			p1=genNewPoint();
			continue;
		}
		for(int i = 2 ; i <= size ; i++)
		{
			if(arr[i].x == p1.x && arr[i].y == p1.y)
			{
				p1=genNewPoint();
				continue;
			}
		}
		break;
	}
}

bool readFile(string inp, int &n , int &m , point &apple , point &unknown , int &size, point* &snake, int &chance , int &ban)
{
	inp+=".dat";
	fstream file(inp);
	if(file.is_open())
	{
		string line;
		getline(file,line);
		chance=stoi(line.substr(0,line.find(' ')));
		ban=stoi(line.substr(line.find(' ')+1));

		getline(file,line);
		n=stoi(line.substr(0,line.find(' ')));
		m=stoi(line.substr(line.find(' ')+1));

		getline(file,line);
		apple.x=stoi(line.substr(0,line.find(' ')));
		apple.y=stoi(line.substr(line.find(' ')+1));

		getline(file,line);
		unknown.x=stoi(line.substr(0,line.find(' ')));
		unknown.y=stoi(line.substr(line.find(' ')+1));
		for (int i = 0 ; getline(file, line ) ; i++)
		{
			snake[i].x=stoi(line.substr(0,line.find(' ')));
			snake[i].y=stoi(line.substr(line.find(' ')+1));
			size=i;
		}
		cout<<"load done\n";
		return 1;
	}else
	{
		cout<<"file doesn't open :(\n";
		return 0;
	}
}
void save(int n , int m ,point apple , point unknown , point* snake, int size, int chance , int ban)
{
	ofstream file;
	file.open("save.dat");
	file<<chance<<' '<<ban<<endl;
	file<<n<<' '<<m<<endl;
	file<<apple.x<<' '<<apple.y<<endl;
	file<<unknown.x<<' '<<unknown.y<<endl;
	for( int i = 0 ; i <= size-1 ; i++)
	{
		file<<snake[i].x<<' '<<snake[i].y<<endl;
	}
	file.close();
}
void showShape()
{
	int n=10;
	int a[100][100]={};
	for(int i=1;i<=n;i++)
	{
		int p=1;
		for(int j=1;j<=(2*n)-(2*i);j++,p++)
			a[i][p]=0;
		for(int j=1;j<=i;j++,p+=2)
		{
			a[i][p]=j;a[i][p+1]=0;
		}
		for(int j=i-1;j>=1;j--,p+=2)
		{
			a[i][p]=j;a[i][p+1]=0;
		}
		for(int j=1;j<=(2*n)-(2*i);j++,p++)
			a[i][p]=0;
	}
	for(int i=1;i<=n;i++)
	{
		int p=1;
		for(int j=1;j<=2*i;j++,p++)
			a[i+n][p]=0;
		for(int j=1;j<=n-i;j++,p+=2)
		{
			a[i+n][p]=j;a[i+n][p+1]=0;
		}
		for(int j=n-i-1;j>=1;j--,p+=2)
		{
			a[i+n][p]=j;a[i+n][p+1]=0;
		}
		for(int j=1;j<=2*i;j++,p++)
			a[i+n][p]=0;
		cout<<endl;
	}
	for(int i=1 ; i<= 2*n;i++)
	{
		for (int j =1 ; j<= 4*n; j++)
		{
			if(a[i][j]==0)
			{
				cout<<' ';
			}else
				cout<<"snake "<<a[i][j];
		}
		cout<<endl;
	}
}
void menu(int &n , int &m , point &apple , point &unknown , int &size, point* &snake ,int &chance , int &ban)
{
	showShape();
	int p;
    printString("which snake is different? if you say right you give an gift.\n");
	p=getche();
	cout<<"\nwrong answer :)))\n\n\n\n";
	cout<<"1-load\n2-play\n3-guide\n";
	cin>>p;
	if(p==1)
	{
		string l;
		cout<<"enter filename that has our format:\n";
		cin>>l;
		if(!readFile(l, n , m , apple , unknown , size, snake , chance, ban))
		{
			snake[1]=genNewPoint();
			apple=genNewPoint();
			unknown=genNewPoint();
		}
	}else if(p==2)
	{
		snake[1]=genNewPoint();
		apple=genNewPoint();
		unknown=genNewPoint();
		return;
	}else if(p==3)
	{
        printString("w-> up ,s-> down ,d-> left ,a-> right at first start going up\nWhen you eat (?),a random thing will happen to you\nWhen you eat (⍟),you grow up\nYou can save game just a check points with press (o).\n\n");
		snake[1]=genNewPoint();
		apple=genNewPoint();
		unknown=genNewPoint();
	}
}
void run()
{
    int wide=30,hi=30;
    int table[wide+2][hi+2]={},size=1,chance=0,ban=0;
    point* snake= new point [225];
    point apple,unknown;
    srand(time(0));
    snake[0]={0,0};
    menu(wide ,hi ,apple ,unknown ,size, snake , chance ,ban );
    bool firstTime=true;
    char input;
    point inp={-1,0};
    bool heart=0;
    while(true)
    {
        if(heart)
        {
            cout<<"\n OPPS game over\n";
            exit(0);
        }
        if(kbhit())
        {
            point befor=inp;
            input=(char)getche();
            if(input == 'a')
            {
                inp.x=0;
                inp.y=-1;
            }else if(input == 'w')
            {
                inp.x=-1;
                inp.y=0;
            }
            else if(input == 's')
            {
                inp.x=1;
                inp.y=0;
            }else if(input == 'd')
            {
                inp.x=0;
                inp.y=1;
            }else
            {
                if(input=='o')
                {
                    save(wide ,hi ,apple , unknown , snake, size, chance , ban);
                    cout<<" save complete \n";
                    sleep(4);
                    continue;
                }
                if(input=='l')
                {
                    exit(0);
                }
                cout<<"invalid\n";
                continue;
            }
            if(inp.x== -1*befor.x || inp.y==-1*befor.y)
            {
                inp=befor;
                continue;
            }
        }
        system("cls");

        point temp[size+2]={};
        for(int i = 1 ; i <= size-1 ; i++)
        {
            temp[i+1]=snake[i];
        }

        snake[1].x+=inp.x;
        snake[1].y+=inp.y;
        if(snake[1].x>wide)
        {
            if(!chance)
            {
                heart=1;
            }else
            {
                cout<<"your chance reduced\n";
                chance--;
            }
        }else if(snake[1].x<1)
        {
            if(!chance)
            {
                heart=1;
            }else
            {
                cout<<"your chance reduced\n";
                chance--;
            }
        }
        else if(snake[1].y>hi)
        {
            if(!chance)
            {
                heart=1;
            }else
            {
                cout<<"your chance reduced\n";
                chance--;
            }

        }else if(snake[1].y<1)
        {
            if(!chance)
            {
                heart=1;
            }else
            {
                cout<<"your chance reduced\n";
                chance--;
            }
        }

        if(snake[1].x == apple.x && snake[1].y == apple.y)
        {
            if(ban>0)
            {
                ban--;
                cout<<"your deprivation  reduced\n";
            }else
            {
                apple=genNewPoint();
                size++;
            }
        }

        if(snake[1].x == unknown.x && snake[1].y == unknown.y)
        {
            int ran=(2-rand()%4);
            if(ran==0)
            {
                cout<<"nothing :)))))\n";
            }else if(ran>0)
            {
                chance+=ran;
                cout<<"congratulations!!!!! you win "<<ran << " more change to play\n";
            }else if(ran<0)
            {
                ban+=-1*ran;
                cout<<"Unfortunately you have banned for "<<-1*ran << " more rounds \n When you eat an apple, your deprivation will be reduced\n ";
            }
            unknown=genNewPoint();
        }

        check(temp , snake[1] , size , apple);
        check(temp , snake[1] , size , unknown);
        table[unknown.x][unknown.y] = -2;
        table[apple.x][apple.y] = -1;

        table[snake[1].x][snake[1].y]=1;
        for(int i = 2 ; i <= size ; i++)
        {
            if(snake[1].x== snake[i].x && snake[1].y == snake[i].y)
            {
                if(!chance)
                {
                    heart=1;
                }else
                {
                    cout<<"your chance reduced\n";
                    chance--;
                }
            }
            snake[i]=temp[i];
            table[snake[i].x][snake[i].y]=i;
        }
        if(size%5==0)
        {
            cout<<"checkpoint \n";
        }
        cout<<"your chance:\n";
        for(int i = 1 ; i <= chance ; i++ )
        {
            cout<<"❤"<<' ';
        }

        cout<<"\nyour deprivation:\n";
        for(int i = 1 ; i <= ban ; i++ )
        {
            cout<<"⚠"<<' ';
        }
        cout<<endl;
        cout<<"enter l to exit;\nenter o to save;\n";
        for(int i = 1 ; i <= wide+2 ; i++ )
        {
            cout<<"⁃⁃";
        }
        cout<<endl;
        for(int i = 1 ; i <= wide ; i++)
        {
            cout<<'|';
            for(int j = 1 ; j <=  hi ; j++)
            {
                if(table[i][j]==0)
                {
                    cout<<"  ";
                }else if(table[i][j]>0)
                {
                    if(table[i][j]==1)
                    {
                        cout<<"■ ";
                    }else
                    {
                        cout<<"◽ ";
                    }
                }else if(table[i][j]==-1)
                {
                    cout<<"• ";
                }else
                {
                    cout<<"? ";
                }
                table[i][j]=0;
            }
            cout<<'|'<<endl;
        }
        for(int i = 1 ; i <= wide+2 ; i++ )
        {
            cout<<"⁃⁃";
        }
        cout<<endl;
        usleepNew(900);
        if(firstTime)
        {
            firstTime=false;
            printString("press w to start\n");
            getche();
        }
    }
}