#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>
using namespace std;

class FileSystem
{
protected:
    FileSystem *Parent;
    string name;

public:
    virtual FileSystem *open(string str = "") = 0;
    FileSystem *close()
    {
        if (this->Parent == this)
        {
            exit(0);
        }
        system("cls");
        return this->Parent;
    };
    string printLocation(string childTree = "")
    {

        if (this->Parent == nullptr)
        {
            cout << this->name << "/" << childTree;
            return "";
        }

        return this->Parent->printLocation(this->name + "/" + childTree);
    };
    string getName() { return this->name; }
    FileSystem *getParent() { return this->Parent; }
    virtual bool isFile() = 0;
};

class File : public FileSystem
{
public:
    File(string Name, FileSystem *Parent)
    {
        this->name = Name;
        this->Parent = Parent;
    }
    virtual FileSystem *open(string str = "") override
    {
        system("cls");
        cout << "> " << this->name << "is Opened \n";
        return this;
    }
    bool isFile() override { return 1; }
};
class Folder : public FileSystem
{
protected:
    unordered_map<string, FileSystem *> folderContent;

public:
    Folder(string Name, FileSystem *Parent)
    {
        this->name = Name;
        this->Parent = Parent;
    }
    void dir()
    {
        cout << endl;
        for (auto ele : folderContent)
        {
            cout << ele.first << endl;
        }
    }
    FileSystem *open(string str = "")
    {
        if (folderContent.size() == 0 || str == "" || folderContent.find(str) == folderContent.end())
        {
            return this;
        }
        if(folderContent[str]->isFile())
        {
            folderContent[str]->open();
            return this;
        }
        return folderContent[str];
    }
    bool isFile() { return 0; }
    FileSystem *add(string name, FileSystem *parent, bool isFile = 1)
    {
        if (isFile)
        {
            folderContent[name] = new File(name, parent);
        }
        else
            folderContent[name] = new Folder(name, parent);
        return folderContent[name];
    }
    void remove(string name = "")
    {
        if (name == "" || folderContent.find(name) == folderContent.end())
            return;
        delete (folderContent[name]);
        folderContent.erase(name);
    }
};
class System
{
public:
    System(string sys)
    {
        FileSystem *system = new Folder(sys, nullptr);
        FileSystem *current = system;
        while (1)
        {
            current->printLocation();
            string command, name;
            cin >> command;
            if (command == "open")
            {
                cin >> name;
                current = current->open(name);
            }
            if (command == "close")
            {
                cout << "closing..";
                current = current->close();
            }
            if (command == "remove")
            {
               
                cin >> name;
                Folder *currentFolder = (Folder *)current;
                currentFolder->remove(name);
                
            }
            if (command == "add" && !current->isFile())
            {
                bool isFile = 0;
                cin >> name;
                cout << "isFile\t";
                cin >> isFile;
                Folder *currentFolder = (Folder *)current;
                currentFolder->add(name, current, isFile);
            }
            if (command == "dir" && !current->isFile())
            {
                Folder *currentFolder = (Folder *)current;
                currentFolder->dir();
            }
        }
    }
};

int main()
{
    System system("windows");
    return 0;
}
