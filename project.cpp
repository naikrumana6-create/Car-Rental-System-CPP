#include <iostream>
#include <fstream>
using namespace std;

class Vehicle
{
public:
    void showType()
    {
        cout << "Vehicle Type: Car\n";
    }
};

class Car : public Vehicle
{
public:
    int id;
    string brand;
    string model;
    int year;
    bool rented;

    Car()
    {
        id = 0;
        brand = "";
        model = "";
        year = 0;
        rented = false;
    }

    Car(int i, string b, string m, int y, bool r)
    {
        id = i;
        brand = b;
        model = m;
        year = y;
        rented = r;
    }

    void display()
    {
        showType();
        cout << "Car ID: " << id << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;

        if (rented)
            cout << "Status: Rented\n";
        else
            cout << "Status: Available\n";

        cout << "------------------------\n";
    }
};

Car cars[100];
int carCount = 0;

void loadCars()
{
    ifstream file("cars.txt");

    while (file >> cars[carCount].id
                >> cars[carCount].brand
                >> cars[carCount].model
                >> cars[carCount].year
                >> cars[carCount].rented)
    {
        carCount++;
    }

    file.close();
}

void saveCars()
{
    ofstream file("cars.txt");

    for (int i = 0; i < carCount; i++)
    {
        file << cars[i].id << " "
             << cars[i].brand << " "
             << cars[i].model << " "
             << cars[i].year << " "
             << cars[i].rented << endl;
    }

    file.close();
}

void addCar()
{
    int id, year;
    string brand, model;

    cout << "Enter Car ID: ";
    cin >> id;

    cout << "Enter Brand: ";
    cin >> brand;

    cout << "Enter Model: ";
    cin >> model;

    cout << "Enter Year: ";
    cin >> year;

    cars[carCount] = Car(id, brand, model, year, false);
    carCount++;

    saveCars();

    cout << "Car added successfully\n";
}

void rentCar()
{
    int id;
    cout << "Enter Car ID to rent: ";
    cin >> id;

    for (int i = 0; i < carCount; i++)
    {
        if (cars[i].id == id)
        {
            if (!cars[i].rented)
            {
                cars[i].rented = true;
                cout << "Car rented successfully\n";
            }
            else
            {
                cout << "Car already rented\n";
            }

            saveCars();
            return;
        }
    }

    cout << "Car not found\n";
}

void displayCars()
{
    if (carCount == 0)
    {
        cout << "No cars available\n";
        return;
    }

    for (int i = 0; i < carCount; i++)
    {
        cars[i].display();
    }
}

int main()
{
    loadCars();

    int choice;

    do
    {
        cout << "\n===== Car Rental System =====\n";
        cout << "1. Add Car\n";
        cout << "2. Rent Car\n";
        cout << "3. Display Cars\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addCar();
            break;

        case 2:
            rentCar();
            break;

        case 3:
            displayCars();
            break;

        case 4:
            cout << "Program Ended\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}