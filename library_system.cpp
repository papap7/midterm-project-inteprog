// STL and vector are not used in this code.
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool isValidChoice(const string &input)
{
    return input.length() == 1 && input[0] >= '1' && input[0] <= '7';
}

bool isValidCategory(const string &input)
{
    return input == "Fiction" || input == "fiction" || input == "FICTION" || input == "Non-Fiction" || input == "non-fiction" || input == "NON-FICTION";
}

bool isValidId(const string &input)
{
    if (input.length() != 3)
    {
        return false;
    }
    for (char c : input)
    {
        if (!isalnum(c))
        {
            return false;
        }
    }
    return true;
}

bool isValidIsbn(const string &input)
{
    if (input.length() != 10 && input.length() != 13)
    {
        return false;
    }
    for (char c : input)
    {
        if ((!isdigit(c) && c != '-') || isspace(c))
        {
            return false;
        }
    }
    return true;
}

bool isValidTitle(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    bool hasNonSpace = false;
    for (char c : input)
    {
        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidAuthor(const string &input)
{
    if (input.empty())
    {
        return false;
    }
    bool hasNonSpace = false;

    for (char c : input)
    {
        if (!(isalpha(c) || c == ' ' || c == '-' || c == '\'' || c == '.'))
        {
            return false;
        }
        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidEdition(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    bool hasNonSpace = false;
    for (char c : input)
    {
        if (!(isalnum(c) || c == ' '))
        {
            return false;
        }

        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidPublication(const string &input)
{
    if (input.length() != 4)
    {
        return false;
    }
    for (char c : input)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    int year = stoi(input);
    if (year < 1000 || year > 2025)
    {
        return false;
    }

    return true;
}

bool isValidInteger(const string &input)
{
    if (input.empty())
        return false;
    for (char c : input)
    {
        if (!isdigit(c) && isspace(c))
        {
            return false;
        }
    }
    return true;
}

bool choiceConfirmation()
{
    for (;;)
    {
        char confirmChoice;
        cin >> confirmChoice;
        cin.ignore();
        confirmChoice = tolower(confirmChoice);

        if (confirmChoice == 'y')
        {
            return true;
        }
        else if (confirmChoice == 'n')
        {
            return false;
        }
        else
        {
            cout << "Invalid input. Please enter [Y] Yes or [N] No.\n";
        }
    }
}

class LibrarySystem
{
public:
    virtual void addBook() = 0;
    virtual void editBook() = 0;
    virtual void searchBook() = 0;
    virtual void deleteBook() = 0;
    virtual void viewBookByCategory() = 0;
    virtual void viewAllBooks() = 0;
    virtual ~LibrarySystem() {}
};

class Book
{
private:
    string id;
    string isbn;
    string title;
    string author;
    string edition;
    string publication;
    string category;

public:
    Book(string id, string isbn, string title, string author, string edition, string publication, string category)
    {
        this->id = id;
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }

    string getId() const
    {
        return id;
    }
    string getIsbn() const
    {
        return isbn;
    }
    string getTitle() const
    {
        return title;
    }
    string getAuthor() const
    {
        return author;
    }
    string getEdition()
    {
        return edition;
    }
    string getPublication() const
    {
        return publication;
    }
    string getCategory() const
    {
        return category;
    }

    void setIsbn(const string &newIsbn)
    {
        isbn = newIsbn;
    }
    void setTitle(const string &newTitle)
    {
        title = newTitle;
    }
    void setAuthor(const string &newAuthor)
    {
        author = newAuthor;
    }
    void setEdition(const string &newEdition)
    {
        edition = newEdition;
    }
    void setPublication(const string &newPublication)
    {
        publication = newPublication;
    }
    void setCategory(const string &newCategory)
    {
        category = newCategory;
    }
};

class Library : public LibrarySystem
{
private:
    static const int size = 10;
    Book *books[size] = {nullptr};

public:
    ~Library()
    {
        for (int i = 0; i < size; i++)
        {
            delete books[i];
            books[i] = nullptr;
        }
    }

    void addBook() override
    {
        cout << "\n- - - - - - - - - - Add Book - - - - - - - - - - \n";
        cout << "Adding Book to Library...\n";
        string id, isbn, title, author, edition, publication, category;
        for (;;)
        {
            cout << "Input Category (FICTION | NON-FICTION): ";
            getline(cin, category);
            if (isValidCategory(category) == false)
            {
                cout << "Category not found! Please enter either FICTION or NON-FICTION.\n";
                continue;
            }
            for (char &c : category)
            {
                if (isalpha(c))
                    c = toupper(c);
            }
            cout << "Category is valid! Book category: " << category << "\n- - - - - - - Book Details - - - - - - -\n";
            break;
        }

        for (;;)
        {
            cout << "Input Book ID (XXX): ";
            getline(cin, id);

            if (!isValidId(id))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }

            for (char &c : id)
            {
                if (isalpha(c))
                {
                    c = toupper(c);
                }
            }

            bool exists = false;
            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getId() == id)
                {
                    cout << "ID already exists. Please enter a different ID.\n";
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                break;
            }
        }

        cout << "ID is valid! Book ID: " << id << "\n";

        for (;;)
        {
            cout << "Enter ISBN: ";
            getline(cin, isbn);

            if (!isValidIsbn(isbn))
            {
                cout << "Invalid ISBN. Please enter a valid ISBN.\n";
                continue;
            }

            bool exists = false;
            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getIsbn() == isbn)
                {
                    cout << "ISBN already exists. Please enter a different ISBN.\n";
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                break;
            }
        }

        cout << "ISBN is valid! Book ISBN: " << isbn << "\n";
        for (;;)
        {
            cout << "Enter Title: ";
            getline(cin, title);
            if (isValidTitle(title) == false)
            {
                cout << "Invalid title. Please enter a valid title.\n";
                continue;
            }
            break;
        }

        for (;;)
        {
            cout << "Enter Author: ";
            getline(cin, author);
            if (isValidAuthor(author) == false)
            {
                cout << "Invalid author. Please enter a valid author.\n";
                continue;
            }
            break;
        }

        for (;;)
        {
            cout << "Enter Edition: ";
            getline(cin, edition);
            if (isValidEdition(edition) == false)
            {
                cout << "Invalid edition. Please enter a valid edition.\n";
                continue;
            }
            break;
        }

        for (;;)
        {
            cout << "Enter Publication Year: ";
            getline(cin, publication);
            if (isValidPublication(publication) == false)
            {
                cout << "Invalid publication year. Please enter a valid publication year.\n";
                continue;
            }
            break;
        }

        cout << "\n- - - - - - - Book Details - - - - - - -\n";
        cout << "ID: " << id << "\n"
             << "ISBN: " << isbn << "\n"
             << "Title: " << title << "\n"
             << "Author: " << author << "\n"
             << "Edition: " << edition << "\n"
             << "Publication Year: " << publication << "\n"
             << "Category: " << category << "\n";
        cout << endl;
        for (;;)
        {
            cout << "Confirm this book details? [(Y) Yes | (N) No] ";
            if (choiceConfirmation() == false)
            {
                Library::addBook();
            }
            break;
        }

        bool bookAdded = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] == nullptr)
            {
                books[i] = new Book(id, isbn, title, author, edition, publication, category);
                cout << "Book added successfully.\n";
                bookAdded = true;
                break;
            }
        }
        if (!bookAdded)

        {
            cout << "Library is full. Cannot add more books.\n";
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    void editBook() override
    {
        cout << "\n- - - - - - - - - - Edit Book - - - - - - - - - -\n";

        bool hasBooks = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr)
            {
                hasBooks = true;
                break;
            }
        }

        if (!hasBooks)
        {
            cout << "No books available.\nPress Enter to continue...";
            cin.get();
            return;
        }

        string id;
        int index = -1;

        while (true)
        {
            cout << "Enter Book ID to edit: ";
            getline(cin, id);

            if (!isValidId(id))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }

            for (char &c : id)
            {
                c = toupper(c);
            }

            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getId() == id)
                {
                    index = i;
                    break;
                }
            }

            if (index != -1)
            {
                break;
            }

            cout << "Book with ID " << id << " not found.\n";
            cout << "Do you want to continue searching? [(Y) Yes | (N) No] ";

            if (!choiceConfirmation())
                return;
        }

        Book *book = books[index];

        while (true)
        {
            string isbn, title, author, edition, publication, category;

            cout << "\nCurrent Details for book ID [" << book->getId() << "]:\n";
            cout << "ISBN: " << book->getIsbn() << "\n";
            cout << "Title: " << book->getTitle() << "\n";
            cout << "Author: " << book->getAuthor() << "\n";
            cout << "Edition: " << book->getEdition() << "\n";
            cout << "Publication Year: " << book->getPublication() << "\n";
            cout << "Category: " << book->getCategory() << "\n";

            cout << "\nEnter new details (press Enter to keep current values):\n";

            while (true)
            {
                cout << "Category (FICTION | NON-FICTION): ";
                getline(cin, category);
                if (category.empty() || isValidCategory(category))
                {
                    for (char &c : category)
                        c = toupper(c);
                    break;
                }
                cout << "Invalid Category. Try again.\n";
            }
            if (category.empty())
                category = book->getCategory();

            while (true)
            {
                cout << "ISBN: ";
                getline(cin, isbn);
                if (isbn.empty() || isValidIsbn(isbn))
                    break;
                cout << "Invalid ISBN. Try again.\n";
            }
            if (isbn.empty())
                isbn = book->getIsbn();

            while (true)
            {
                cout << "Title: ";
                getline(cin, title);
                if (title.empty() || isValidTitle(title))
                    break;
                cout << "Invalid Title. Try again.\n";
            }
            if (title.empty())
                title = book->getTitle();

            while (true)
            {
                cout << "Author: ";
                getline(cin, author);
                if (author.empty() || isValidAuthor(author))
                    break;
                cout << "Invalid Author. Try again.\n";
            }
            if (author.empty())
                author = book->getAuthor();

            while (true)
            {
                cout << "Edition: ";
                getline(cin, edition);
                if (edition.empty() || isValidEdition(edition))
                    break;
                cout << "Invalid Edition. Try again.\n";
            }
            if (edition.empty())
                edition = book->getEdition();

            while (true)
            {
                cout << "Publication Year: ";
                getline(cin, publication);
                if (publication.empty() || isValidPublication(publication))
                    break;
                cout << "Invalid Publication Year. Try again.\n";
            }
            if (publication.empty())
                publication = book->getPublication();

            cout << "\nUpdated Details for book ID [" << book->getId() << "]:\n";
            cout << "ISBN: " << isbn << "\n";
            cout << "Title: " << title << "\n";
            cout << "Author: " << author << "\n";
            cout << "Edition: " << edition << "\n";
            cout << "Publication Year: " << publication << "\n";
            cout << "Category: " << category << "\n";

            cout << "Confirm changes? [(Y) Yes | (N) No] ";
            if (choiceConfirmation())
            {
                book->setIsbn(isbn);
                book->setTitle(title);
                book->setAuthor(author);
                book->setEdition(edition);
                book->setPublication(publication);
                book->setCategory(category);

                cout << "Book details updated successfully.\n";
                break;
            }
            else
            {
                cout << "Edit cancelled. Retry updating details.\n";
                cout << "Press Enter to continue...";
                cin.get();
            }
        }
    }

    void searchBook() override
    {
        cout << "\n- - - - - - - - - - Search Book - - - - - - - - - -\n";

        bool hasBooks = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr)
            {
                hasBooks = true;
                break;
            }
        }

        if (!hasBooks)
        {
            cout << "No books available.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        string id;
        int index = -1;

        for (;;)
        {
            cout << "Enter Book ID to search: ";
            getline(cin, id);
            if (isValidId(id) == false)
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            for (char &c : id)
            {
                c = toupper(c);
            }

            index = -1;
            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getId() == id)
                {
                    index = i;
                    break;
                }
            }

            if (index != -1)
            {
                break;
            }

            cout << "Book with ID " << id << " not found.\n";

            cout << "Do you want to continue searching for a book? [(Y) Yes | (N) No] ";
            if (choiceConfirmation() == false)
            {
                return;
            }
        }

        Book *book = books[index];

        cout << "\nDetails of the book ID [" << book->getId() << "]:\n";
        cout << "ISBN: " << book->getIsbn() << "\n";
        cout << "Title: " << book->getTitle() << "\n";
        cout << "Author: " << book->getAuthor() << "\n";
        cout << "Edition: " << book->getEdition() << "\n";
        cout << "Publication Year: " << book->getPublication() << "\n";
        cout << "Category: " << book->getCategory() << "\n";

        cout << "Press Enter to continue...";
        cin.clear();
        cin.get();
    }

    void deleteBook() override
    {
        cout << "\n- - - - - - - - - - Delete Book - - - - - - - - - - \n";
        string id;

        for (;;)
        {
            cout << "Enter Book ID to search: ";
            getline(cin, id);

            if (!isValidId(id))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }

            for (char &c : id)
            {
                c = toupper(c);
            }

            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getId() == id)
                {
                    cout << "Book with ID " << id << " found.\n";
                    cout << "Are you sure you want to delete this book? [(Y) Yes | (N) No]: ";
                    if (choiceConfirmation() == true)
                    {
                        delete books[i];
                        books[i] = nullptr;
                        cout << "Book deleted successfully.\n";
                    }
                    else
                    {
                        cout << "Deletion cancelled.\n";
                    }
                    return;
                }
            }

            cout << "Book with ID " << id << " not found.\n";
        }
    }

    void viewBookByCategory() override
    {
        cout << "\n- - - - - - - - - - View Books by Category - - - - - - - - - -\n";

        bool hasBooks = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr)
            {
                hasBooks = true;
                break;
            }
        }

        if (!hasBooks)
        {
            cout << "No books available.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        string category;
        for (;;)
        {
            cout << "Enter category (FICTION | NON-FICTION): ";
            getline(cin, category);

            if (!isValidCategory(category))
            {
                cout << "Invalid category! Please enter FICTION or NON-FICTION.\n";
                continue;
            }

            for (char &c : category)
            {
                if (isalpha(c))
                    c = toupper(c);
            }
            break;
        }

        cout << "\nShowing books in category: " << category << "\n";
        cout << left
             << setw(10) << "ID"
             << setw(20) << "ISBN"
             << setw(25) << "TITLE"
             << setw(25) << "AUTHOR"
             << setw(15) << "EDITION"
             << setw(15) << "PUBLICATION"
             << "\n";
        cout << string(110, '-') << "\n";

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr && books[i]->getCategory() == category)
            {
                cout << left
                     << setw(10) << books[i]->getId()
                     << setw(20) << books[i]->getIsbn()
                     << setw(25) << books[i]->getTitle()
                     << setw(25) << books[i]->getAuthor()
                     << setw(15) << books[i]->getEdition()
                     << setw(15) << books[i]->getPublication()
                     << "\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books found in this category.\n";
        }

        cout << "Press Enter to continue...";
        cin.get();
    }

    void viewAllBooks() override
    {
        cout << "\n"
             << string(59, ' ') << "List of Books" << string(59, ' ') << "\n"
             << string(130, '-') << "\n"
             << left
             << setw(10) << "ID"
             << setw(20) << "ISBN"
             << setw(25) << "TITLE"
             << setw(25) << "AUTHOR"
             << setw(15) << "EDITION"
             << setw(15) << "PUBLICATION"
             << setw(15) << "CATEGORY"
             << "\n";
        cout << string(130, '-') << "\n";

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr)
            {
                cout << left
                     << setw(10) << books[i]->getId()
                     << setw(20) << books[i]->getIsbn()
                     << setw(25) << books[i]->getTitle()
                     << setw(25) << books[i]->getAuthor()
                     << setw(15) << books[i]->getEdition()
                     << setw(15) << books[i]->getPublication()
                     << setw(15) << books[i]->getCategory()
                     << "\n";
                found = true;
            }
        }
        if (!found)
        {
            cout << "No books available.\n";
        }
        cout << "Press Enter to continue to menu...";
        cin.get();
    }
};

void displayMenu(Library &libraryInstance)
{
    cout << "\nLibrary Management System\n"
         << "- - - - - - - - - - - - - - - - - - - - - -\n"
         << "1. Add Book\n"
         << "2. Edit Book\n"
         << "3. Search Book\n"
         << "4. Delete Book\n"
         << "5. View Book by Category\n"
         << "6. View All Books\n"
         << "7. Exit\n"
         << endl;
    int numChoice;
    for (;;)
    {
        cout << "Input number of choice (1 - 7): ";
        string choice;
        getline(cin, choice);
        if (isValidChoice(choice) == false)
        {
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }
        numChoice = stoi(choice);
        break;
    }

    switch (numChoice)
    {
    case 1:
        libraryInstance.addBook();
        displayMenu(libraryInstance);
        return;
    case 2:
        libraryInstance.editBook();
        displayMenu(libraryInstance);
        return;
    case 3:
        libraryInstance.searchBook();
        displayMenu(libraryInstance);
        return;
    case 4:
        libraryInstance.deleteBook();
        displayMenu(libraryInstance);
    case 5:
        libraryInstance.viewBookByCategory();
        displayMenu(libraryInstance);
        return;
    case 6:
        libraryInstance.viewAllBooks();
        displayMenu(libraryInstance);
        return;
    case 7:
        cout << "Exiting the program.\n";
        exit(0);
        break;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        displayMenu(libraryInstance);
        return;
    }
}

int main()
{
    Library *libraryInstance = new Library();
    displayMenu(*libraryInstance);

    return 0;
}