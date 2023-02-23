#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

using namespace std;

int main();//declared main in order to call it before definition
void check_exist(char[]);//Functio to check if entered username already exists
void validate_username(char[], int);//to validate username with password
void main_menu();
void home();

void gotoxy(int x, int y) {
    static HANDLE h;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x,y };
    SetConsoleCursorPosition(h, c);
}
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
void register_user();
void login_user();
void main_menu();
class employee
{
    int employee_id;
    char employee_name[50];
    char employee_department[20];
    int employee_shift;
    char username[20]; int password;

public:
    float basic_slry, daily_a, income_tax, gross_salary, net_salary;
    void loggin_details()
    {
        cout << "Enter Username: ";
        cin >> username;
        check_exist(username);
        cout << "Enter Password: ";
        cin >> password;
    }
    void login() {
        cout << "\nEnter Username: ";
        cin >> username;
        cout << "\nEnter Password: ";
        cin >> password;
        validate_username(username, password);
    }
    void getdata() {
        cout << "Enter Employees Name :";
        cin >> employee_name;
        cout << "\nEnter Employees ID :";
        cin >> employee_id;
        cout << "Enter Employees Department :";
        cin >> employee_department;
        cout << "Enter Employee shift :";
        cin >> employee_shift;
        cout << "\nEnter Employees Salary :";
        cin >> basic_slry;
    }
    float calculate_net_salary()
    {
        // basic_slry, daily_a, income_tax, gross_salary, net_salary
        daily_a = (basic_slry * 5)/100;
        gross_salary = basic_slry + daily_a;
        income_tax = gross_salary * 0.30;
        net_salary = (basic_slry + daily_a) - income_tax;
        return net_salary;
    }
    void showdata()
    {
        net_salary = calculate_net_salary();

        cout << "Employees Name:" << employee_name << endl;
        cout << "Employees ID:" << employee_id << endl;
        cout << "Employees Department:" << employee_department << endl;
        cout << "Employees Shift:" << employee_shift << endl;
        cout << "Employees Basic Salary:" << basic_slry << endl;
        cout << "Employees Net Salary:" << net_salary << endl;
    }
    void show_tabular()
    {
        cout << employee_name << setw(10) << employee_id << setw(12) << employee_department << setw(10) << employee_shift << setw(12) << endl;
    }
    int  retemployee_id()
    {
        return employee_id;
    }

    string ret_username() {
        return username;
    }
    int ret_password() {
        return password;
    }

};

void check_exist(char nm[])
{
    fstream fp;
    employee one{};
    char ch;
    fp.open("password.dat", ios::in | ios::out);
    while (fp.read((char*)&one, sizeof(employee)))
    {
        if (one.ret_username() == nm) {
            cout << "\nUsername already exists";
            cout << "\nBack to main menu [y,n] ";
            ch = getch();
            switch (ch)
            {
            case 'y':
                main();
                break;
            case 'Y':
                main();
                break;
            case 'n':
                exit(0);
                break;
            case 'N':
                exit(0);
                break;

            default:
                cout << "\nInvalid choice";
                break;
            }
        }
        else {
            return;
        }
    }
    fp.close();
}

fstream lpswd;
employee one;
void register_user()
{


    lpswd.open("password.dat", ios::out | ios::in | ios::app | ios::binary);
    one.loggin_details();
    lpswd.write((char*)&one, sizeof(employee));
    lpswd.close();
    cout << "Registered successfully";
    cin.ignore();
    cin.get();
    main();
}
fstream emp;
//employee one;
void write_employee()
{
    emp.open("employee.dat", ios::out | ios::app | ios::binary);
    one.getdata();
    emp.write((char*)&one, sizeof(employee));
    emp.close();
    cout << "\n\nEmployees record Has Been Created %";
    getch();
}

void display_all()
{
    system("cls");
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    emp.open("employee.dat", ios::in|ios::out|ios::binary);
    while (emp.read((char*)&one, sizeof(employee)))
    {
        one.showdata();
        cout << "\n\n====================================\n";
        //_getch();
    }
    emp.close();
    _getch();
}
void display_sp(int n)
{
    int flag = 0;
    emp.open("employee.dat", ios::in|ios::out|ios::binary);
    while (emp.read((char*)&one, sizeof(employee)))
    {
        if (one.retemployee_id() == n)
        {
            system("cls");
            one.showdata();
            flag = 1;
        }
    }
    emp.close();
    if (flag == 0)
        cout << "\n\nrecord not exist";
    getch();
}
void modify_employee()
{
    int no, found = 0;
    system("cls");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Employees ID";
    cin >> no;
    emp.open("employee.dat", ios::in | ios::out|ios::binary);
    while (emp.read((char*)&one, sizeof(employee)) && found == 0)
    {
        if (one.retemployee_id() == no)
        {
            one.showdata();
            cout << "\nPlease Enter The New Details of Employee" << endl;
            one.getdata();
            int pos = -1 * sizeof(one);
            emp.seekp(pos, ios::cur);
            emp.write((char*)&one, sizeof(employee));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    emp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}

void delete_employee()
{
    int no;
    system("cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The Employees ID You Want To Delete";
    cin >> no;
    emp.open("employee.dat", ios::in | ios::out);
    fstream emp2;
    emp2.open("Tem.dat", ios::out);
    emp.seekg(0, ios::beg);
    while (emp.read((char*)&one, sizeof(employee)))
    {
        if (one.retemployee_id() != no)
        {
            emp2.write((char*)&one, sizeof(employee));
        }
    }
    emp2.close();
    emp.close();
    remove("employee.dat");
    rename("Tem.dat", "employee.dat");
    cout << "\n\n\tRecord Deleted ..";
   // getch();
}

void employee_list()
{
    system("cls");
    emp.open("employee.dat", ios::in|ios::out);


    cout << "\n\n\t\tALL EMPLOYEES LIST \n\n";
    cout << "====================================================\n";
    cout << "employee_id. Employee_name          employee_department employee_shift\n";
    cout << "====================================================\n";

    while (emp.read((char*)&one, sizeof(employee)))
    {
        one.show_tabular();
    }
    emp.close();
    getch();
}void elist()
{
    int ans, idno;
    char ch=0;
    system("cls");
    cout << "\n\n\nLIST MENU";
    cout << "\n\n\n1. employee_list\n\n2. employees details\n\n3.Back to Main Menu";
    cout << "\n\n\nEnter Choice (1/2)? ";
    cin >> ans;
    switch (ans)
    {
    case 1:
        employee_list();
        break;
    case 2:
    {
        do
        {
            system("cls");
            char ans;
            cout << "\n\nEnter Employees ID : ";
            cin >> idno;
            display_sp(idno);
            cout << "\n\nDo you want to See More Result (y/n)?";
            cin >> ans;
        } while (ans == 'y' || ans == 'Y');

        break;
    }
    case 3:
        break;
    default:
        cout << "\a";
    }
}
void intro()
{
    system("cls");
    gotoxy(35, 11);
    cout << "Employee";
    gotoxy(33, 14);
    cout << "Employee system";
    gotoxy(35, 17);
    cout << "PROJECT";
    cout << "\n\nMADE BY :Peter Michuki";
    cout << "\n\nCONTACT :0797243918";
    getch();

}

void validate_username(char nm[], int pw)
{
    fstream fp;
    employee one{};
    char ch;
    int flag = 0; int found = 0;
    fp.open("password.dat", ios::in|ios::out);
    while (fp.read((char*)&one, sizeof(employee)))
    {
        if (one.ret_username() == nm) {
            flag = 1;
            if (one.ret_password() == pw) {
                found = 1;
                cout << "\nLogin successfull\n";
                cin.ignore();
                cin.get();
                home();
            }

        }
    }

    fp.close();
    if (found == 0) {
        cout << "\nInvalid password";
        cout << "\nBack to main menu [y,n] ";
        ch = getch();
        switch (ch)
        {
        case 'y':
            main_menu();
            break;
        case 'Y':
            main_menu();
            break;
        case 'n':
            exit(0);
            break;
        case 'N':
            exit(0);
            break;

        default:
            cout << "\nInvalid choice";
            main_menu();
            break;
        }
    }
    if (flag == 0) {
        cout << "\nUsername does not exists";
        cout << "\nBack to main menu [y,n] ";
        ch = getch();
        switch (ch)
        {
        case 'y':
            main_menu();
            break;
        case 'Y':
            main_menu();
            break;
        case 'n':
            exit(0);
            break;
        case 'N':
            exit(0);
            break;

        default:
            cout << "\nInvalid choice";
            main_menu();
            break;
        }
    }
}


void login_user()
{
    one.login();
}

void main_menu()
{
    system("cls");
    int choice;
    cout << "1.Register\n2.Login\nYour Choice:";
    cin >> choice;
    switch (choice)
    {
    case 1: system("cls"); register_user(); break;
    case 2: system("cls"); login_user(); break;
    default: cout << "\nInvalid"; break;
    }
    getch();
}

void entry_menu()
{
    system("cls");
    char ch2;
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1.CREATE EMPLOYEE RECORD";
    cout << "\n\n\t2.DISPLAY ALL EMPLOYEES RECORDS";
    cout << "\n\n\t3.SEARCH EMPLOYEE RECORD ";
    cout << "\n\n\t4.MODIFY EMPLOYEE RECORD";
    cout << "\n\n\t5.DELETE EMPLOYEE RECORD";
    cout << "\n\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) ";
    ch2 = getche();
    switch (ch2)
    {
    case '1':
        system("cls");
        write_employee();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        system("cls");
        cout << "\n\n\tPlease Enter The Employees ID number ";
        cin >> num;
        display_sp(num);
        break;
    case '4':
        modify_employee();
        break;
    case '5':
        delete_employee();
        break;
    case '6':
        break;
    default:
        cout << "\a";
        entry_menu();
    }
}
void home()
{
    char ch;
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. LIST MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch)
        {
        case '1':
            system("cls");
            elist();
            break;
        case '2':
            entry_menu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');

}
int main()
{
    intro();
    main_menu();
    home();
    return 0;
}

