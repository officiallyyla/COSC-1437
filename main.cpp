#include <iostream>
#include <fstream>
using namespace std;

// Implement the Pet class
// variables that keep track of the pet's state: hungry, sleepy, bored.
class Pet 
{
protected:
    string name;
    int hungry;
    int sleepy;
    int bored;

public:
Pet(string name) : name(name), hungry(40), sleepy(40), bored(40) {}

string getName() const 
{ 
  return name; 
}

// 3 interaction functions that change those variables. 
virtual void feed() = 0; 

virtual void sleep() = 0;

virtual void play() = 0;

void menu() // Main menu to load a pet, or to create a new pet from the list of available pet types to choose from. 
{
  cout << "-----------Menu-----------" << endl; 
  cout << "- 1. Load existing pet.  -" << endl;
  cout << "- 2. Create new pet.     -" << endl;
  cout << "--------------------------" << endl;
}

void status() 
{
  cout << "-Current Pet Stats-" << endl;
  cout << "Name: " << name << endl; 
  cout << "Hungry lvl: " << hungry << endl; 
  cout << "Sleepy lvl: " << sleepy << endl;
  cout << "Bored lvl: " << bored << endl; 
}

void interactions(){
    cout << "___________________________" << endl;
    cout << "|Menu of Interactions:    |" << endl;
    cout << "| 1. Feed                 |" << endl;
    cout << "| 2. Sleep                |" << endl;
    cout << "| 3. Play                 |" << endl;
    cout << "| 4. Next Hour            |" << endl;
    cout << "| 5. Save                 |" << endl;
    cout << "| 6. Load                 |" << endl;
    cout << "| 7. Exit                 |" << endl;
    cout << "|_________________________|" << endl;
}

void nextHour() // Updates pet's state values to reflect the passage of time. 
{  
  cout << "Next hour later..." << endl;
  
  hungry += 10;
  sleepy += 20;
  bored += 5;
  
  if (hungry > 40)
  {
    cout << name << " is hungry!" << endl;
  }
  if (sleepy > 40) 
  {
    cout << name << " is sleepy!" << endl;
  }
  
  if (bored > 40)
  {
    cout << name << " is bored!" << endl;
  }
}

// To save and load all of its data onto or from a file to allow the player to continue with an existing pet. 
void save(string filename)
{
  ofstream fout(filename);
  if (fout.is_open())
  {
    fout << name << endl;
    fout << hungry << endl;
    fout << sleepy << endl;
    fout << bored << endl;
  }
  fout.close();
}

void load(string filename) 
{
  ifstream fin(filename);
  if (fin.is_open())
  {
    fin >> name;
    fin >> hungry;
    fin >> sleepy;
    fin >> bored;
  }
  else { 
    cout << "File can not be found. Exciting..." << endl;
    exit(0);
  }
  fin.close();
}
};

// Implement Types of Pets
// 3 new child classes that inherit from the above Pet class. 
//Each new Pet type (class) is unique from printing a unique message to change of values for each interaction.
class Dog : public Pet
{
public:
Dog(string name) : Pet(name) {}

void feed() override
{
  hungry -= 10; 
  sleepy += 10;
  cout << name << " *chews bone*" << endl;
}

void sleep() override
{
  sleepy -= 15;
  bored += 20;
  cout << name << " *snores*" << endl;
}

void play() override 
{
  bored -= 5;
  sleepy += 15;
  cout << name << " *barks and play with stuffed toy*" << endl;
}
};

class Cat : public Pet
{
public:
Cat(string name) : Pet(name) {}

void feed() override
{
  hungry -= 15;
  sleepy += 15;
  cout << name << " *nibbles on tuna*" << endl;
}

void sleep() override 
{
  sleepy -= 5; 
  bored += 15;
  cout << name << " *purrs*"  << endl;
}

void play() override
{
  bored -= 10; 
  sleepy += 10; 
  cout << name << " *meows and scratches cat post*" << endl;
}
};

class Bird : public Pet
{
public:
Bird(string name) : Pet(name) {}

void feed() override
{
  hungry -= 20;
  sleepy += 5;
  cout << name << " *pecks at seeds*" << endl;
}

void sleep() override 
{
  sleepy -= 20;
  bored += 5; 
  cout << name << " in *quite sleep*" << endl;
}

void play() override
{
  bored -= 20;
  sleepy += 5;
  cout << name << " *Chirp cHiRp CHIRP....*" << endl;
}
};

// Implement the Game Loop
int main()
{
  
  Pet *pet;
  srand(time(0));
  cout << "Welcome to the Tamagotchi Pet Game:" << endl;
  
  int menuChoice = 0;
  while(menuChoice < 1 || menuChoice > 3)
  {
    pet->menu(); // menu to load a pet or to create a new pet from the list of available pet types to choose from. 
    cin >> menuChoice;
    while(menuChoice < 1 || menuChoice > 2)
    {
      cout << "Invalid, please choose 1 or 2." << endl;
      cin >> menuChoice;
    }
  }
  
  if(menuChoice == 1)
  {
    string filename;
    cout << "Enter the file name" << endl;
    cin >> filename;
    
    pet = new Dog("temp");
    int petType = 0;
    
    while (petType < 1 || petType > 3)
    {
      cout << "What type of pet was in the filename." << endl;
      cout << "1. Dog" << endl;
      cout << "2. Cat" << endl;
      cout << "3. Bird" << endl;
      cin >> petType;
      
      if(petType < 1 || petType > 3)
      {
        cout << "Invalid. Pick again from 1-3" << endl;
      }
    }
    if(petType == 1)
    {
      pet = new Dog("dog");
    }
    else if(petType == 2)
    {
      pet = new Cat("cat");
    }
    else 
    {
      pet = new Bird("bird");
    }
    pet->load(filename); // restore the name, stats, and status of the pet.
  }
  else 
  {
    int userChoice = 0;
    string name;
    while (userChoice < 1 || userChoice > 3) 
    {
      cout << "Choose a pet type:" << endl;
      cout << "1. Dog" << endl;
      cout << "2. Cat" << endl;
      cout << "3. Bird" << endl;
      cin >> userChoice;
      
      if (userChoice < 1 || userChoice > 3) {
      cout << "Invalid pet type selected. Please choose 1, 2, or 3." << endl;
      }
    }
    
    cout << "Enter a name for your pet: "; 
    cin >> name; // Further game message for the pet is address by its new name. 
    
    if (userChoice == 1) 
    {
      pet = new Dog(name);
    } 
    else if (userChoice == 2) 
    {
      pet = new Cat(name);
    } 
    else 
    {
      pet = new Bird(name);
    }
  }
cout << "You have name your pet- " << pet->getName() << "." << endl;
  cout << "Congrats on your new pet! Having pets is a responsibilty... It is now up to you to take care of your new virtual pet." << endl; 

  cout << endl; 
  
  string saveFilename;
  string loadFilename;
  while (true)
  { 
    pet->status();
    pet->interactions();
    
    //The game present the player with a list of possible interactions, save or load files, or exit the game. 
    int menuInteraction;
    cin >> menuInteraction;
    
    switch (menuInteraction)
    {
      case 1:
        pet->feed();
        break;
      case 2:
        pet->sleep();
        break;
      case 3:
        pet->play();
        break;
      case 4:
        pet->nextHour();
        break;
      case 5:
        cout << "Enter the filename to save: ";
        cin >> saveFilename;
        pet->save(saveFilename);
        break;
      case 6:
        cout << "Enter the filename to load: ";
        cin >> loadFilename;
        pet->load(loadFilename);
        break;
      case 7:
        cout << "Exiting Game... " << endl;
        return 0;
      default:
        cout << "Invalid option. Please try again." << endl;
    }
  }
  return 0;
}
