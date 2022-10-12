#include<iostream>
#include<fstream>
using namespace std;
//Used Classes
class User;
class Comment;
class Post;
class Page;
class Date;
//Helper Class for Calculating the Lenth of a particular String and GetStringFromBuffer
class Helper
{
public:
	static int StringLenght(const char* str)
	{
		int Length = 0;
		for (int i = 0; str[i] != '\0'; i++)
			Length++;
		return Length;
	}

	static char* GetStringFromBuffer(char* str)
	{
		int strLen = StringLenght(str);
		char* mystr = new char[strLen + 1];
		for (int i = 0; str[i] != '\0'; i++)
			mystr[i] = str[i];
		mystr[strLen] = '\0';
		return mystr;
	}
};
//Keeps the ID of all the Posts and Users and Pages
class Object
{
protected:
	char* ID;
public:
	Object()
	{
		ID = nullptr;
	}

	virtual void Set_ID(char* _ID){

	}

	virtual void getname(){

	}

	virtual char* Get_ID() {
		return ID;
	}

	virtual void Add_Post(Post* p){

	}

	virtual ~Object()
	{
		if (ID != nullptr)
		{
			delete[] ID;
		}
	}

};
//Keeps the Record of Pages
class Page :public Object
{
private:
	char* Title;
	static int TotalPages;
	int No_of_TimeLine;
	Post** TimeLine;
public:
	void LoadDataFromFile(ifstream& file)
	{
		char ID[5];		file >> ID;		Set_ID(ID);

		char _Title[150];	file.getline(_Title, 150);		Title = Helper::GetStringFromBuffer(_Title);
	}

	Page()
	{
		Title = nullptr;
		TimeLine = nullptr;
		No_of_TimeLine = 0;
	}

	void getname()
	{
		cout << "  " << Title << " ";
	}

	static void Set_TotalPages(int _TotalPages)
	{
		TotalPages = _TotalPages;
	}

	void Set_ID(char* _ID)
	{
		ID = Helper::GetStringFromBuffer(_ID);
	}

	char* Get_ID()
	{
		return ID;
	}

	static int Get_TotalPages()
	{
		return TotalPages;
	}

	void Set_Title(char* _Title)
	{
		Title = Helper::GetStringFromBuffer(_Title);
	}

	void Add_Post(Post& post)
	{
		if (TimeLine == nullptr)
		{
			TimeLine = new Post * [20];
		}
		TimeLine[No_of_TimeLine] = nullptr;
		TimeLine[No_of_TimeLine] = &post;
		No_of_TimeLine++;
	}

	char* Get_Title()
	{
		return Title;
	}

	void PrintID()
	{
		cout << ID << " ";
	}

	void PrintTitle()
	{
		cout << Title << " ";
	}

	~Page()
	{
		if (Title != nullptr)
		{
			delete Title;
		}
	}
};
//Static Total Pages 
int Page::TotalPages = 0;
//Date Class for Keeping the Record of Current Date and Sets the date
class Date
{
	int day, month, year;
	static Date currentdate;
public:
	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	Date(int dd, int mm, int yy)
	{
		day = dd;
		month = mm;
		year = yy;
	}

	void SetDate(int dd, int mm, int yy)
	{
		day = dd;
		month = mm;
		year = yy;
	}

	Date operator=(Date& d)
	{
		month = d.month;
		day = d.day;
		year = d.year;
		return *this;
	}

	int getday()
	{
		return day;
	}

	int getyear()
	{
		return year;
	}

	int getmonth()
	{
		return month;
	}

	void PrintDate()
	{
		cout << day << " " << month << " " << year << endl;
	}

	~Date()
	{

	}
};
//Static Current Date
Date Date::currentdate(15, 7, 2017);
//Post class keeping the record all the Posts
class Post :public Object
{
private:
	Object* PostedBy;
	Object** LikedBy;
	Comment** comments;
	Date PostedOn;
	char* Text;
	static int No_of_Posts;
	int No_of_comments;
	int No_of_LikedBy;
public:
	Post()
	{
		PostedBy = 0;
		LikedBy = 0;
		Text = 0;
		No_of_LikedBy = 0;
		No_of_comments = 0;
		comments = 0;
	}

	Date Get_PostedOn()
	{
		return PostedOn;
	}

	static void Set_No_of_Posts(int _No_of_Posts)
	{
		No_of_Posts = _No_of_Posts;
	}

	void Add_Comment(Comment& _Comment)
	{
		if (comments == nullptr)
		{
			comments = new Comment * [20];
		}
		
		comments[No_of_comments] = nullptr;
		comments[No_of_comments] = &_Comment;
		
		No_of_comments++;
	}

	static int Get_No_of_Posts()
	{
		return No_of_Posts;
	}

	void Set_Posted_By(Object* _PostedBy)
	{
		PostedBy = _PostedBy;
		cout<<PostedBy->Get_ID()<<"\n";
	}

	void No_of_Liked_By(int _No_of_LikedBy)
	{
		No_of_LikedBy = _No_of_LikedBy;
		if (No_of_LikedBy > 0)
		{
			LikedBy = new Object * [No_of_LikedBy];
		}
	}

	void Set_LikedBy(Object* _LikedBy)
	{
		static int count = 0;
		LikedBy[count] = new Object;
		LikedBy[count] = _LikedBy;
		count++;
	}

	void Set_ID(char* _ID)
	{
		ID = Helper::GetStringFromBuffer(_ID);
	}

	char* Get_ID()
	{
		return ID;
	}

	void Set_Text(char* _Text)
	{
		Text = Helper::GetStringFromBuffer(_Text);
	}

	char* Get_Text()
	{
		return Text;
	}

	virtual void LoadDataFromFile(ifstream& file)
	{
		char* PostID=new char[10];
		file >> PostID;
		Set_ID(PostID);
		cout << Get_ID() << endl;

		int Date = 0, Month = 0, Year = 0;
		file >> Date;
		file >> Month;
		file >> Year;

		PostedOn.SetDate(Date,Month,Year);
		PostedOn.PrintDate();
		
		char* PostText=new char[150];
		file.ignore();
		file.getline(PostText, 150);
		Set_Text(PostText);
		cout<<Get_Text()<<"\n";
	}

};
//Static No of Posts
int Post::No_of_Posts = 0;
//Activity Class for holding Data of Activities and this class is basically the derived one Post class
class Activity :public Post
{
	int Value_Type;
	char* Value;
public:
	Activity()
	{
		Value_Type = 0;
		Value = 0;
	}
	
	void Set_Value_Type(int _Value_Type)
	{
		Value_Type = _Value_Type;
	}

	void Set_Value(char* _Value)
	{
		Value = Helper::GetStringFromBuffer(_Value);
	}

	char* Get_Value()
	{
		return Value;
	}

	int Get_Value_Type()
	{
		return Value_Type;
	}

	void LoadDataFromFile(ifstream& file)
	{
		Post::LoadDataFromFile(file);

		int _Value_Type;
		file >> _Value_Type;
		Set_Value_Type(_Value_Type);
		cout<<Get_Value_Type()<<" ";

		char* _Value=new char[30];
		file.getline(_Value, 150);
		Set_Value(_Value);
		cout << Get_Value() << "\n";

	}
};
//Class Comment which holds the data All the Comments
class Comment :public Object
{
private:
	char* Text;
	Object* CommentedBy;
	static int No_of_Comments;
public:
	Comment()
	{
		Text = 0;
		CommentedBy = 0;
	}

	static void Set_No_of_Comments(int _No_of_Comments)
	{
		No_of_Comments = _No_of_Comments;
	}

	static int Get_No_of_Comments()
	{
		return No_of_Comments;
	}

	void Set_ID(char* _ID)
	{
		ID = Helper::GetStringFromBuffer(_ID);
	}

	char* Get_ID()
	{
		return ID;
	}

	char* Get_Text()
	{
		return Text;
	}

	void Set_CommentedBy(Object* _CommentedBy)
	{
		CommentedBy = _CommentedBy;
	}

	char* Get_CommentedBy()
	{
		return ID;
	}

	void Set_Text(char* _Text)
	{
		Text = Helper::GetStringFromBuffer(_Text);
	}
};
//Static No of Comments
int Comment::No_of_Comments = 0;
//User class holding the data of all the users 
class User :public Object
{
	static int No_of_Users;
	//static char tname;
	int No_of_TimeLine;
	Post** TimeLine;
	char* FirstName;
	char* LastName;
	User** FriendList;
	Page** LikedPages;
	//char** FriendID;
	//char** PagesList;
	int No_of_Liked_Pages;
	int No_of_Friends;
public:

	User()
	{
		FirstName = nullptr;
		LastName = nullptr;
		FriendList = nullptr;
		No_of_Liked_Pages = 0;
		No_of_Friends = 0;
		FriendList = 0;
		LikedPages = 0;
		TimeLine = new Post * [20];
		No_of_TimeLine = 0;

	}

	void Add_Post(Post* post)
	{
		TimeLine[No_of_TimeLine] = new Post();
		TimeLine[No_of_TimeLine] = post;

		cout << "TimeLine:\t" << TimeLine[No_of_TimeLine]->Get_ID() << "\n";

		No_of_TimeLine++;
	}

	void getname()
	{
		cout << "  " << FirstName << "  " << LastName << "  ";
	}

	char* Get_ID()
	{
		return ID;
	}

	void LoadDataFromFile(ifstream& file, char***& tempFriendList, char***& tempLikedPages)
	{
		static int counter = 0;
		
		char _ID[4];			file >> _ID;			this->Set_ID(_ID);

		char _FirstName[20];	file >> _FirstName;		FirstName = Helper::GetStringFromBuffer(_FirstName);

		char _LastName[20];		file >> _LastName;		LastName = Helper::GetStringFromBuffer(_LastName);

		char temp_users[20][20];
		
		int i = 0;
		for (; i < 20; i++)
		{
			file >> temp_users[i];
			if (temp_users[i][0] != 'u')
			{
				temp_users[i][0] = 'h';

				break;
			}
		}
		No_of_Friends = i;
		tempFriendList[counter] = new char* [i + 1];
		for (int a = 0; a < i; a++)
		{
			tempFriendList[counter][a] = Helper::GetStringFromBuffer(temp_users[a]);
		}

		char temp_Pages[20][20];
		i = 0;
		for (; i < 20; i++)
		{
			file >> temp_Pages[i];
			if (temp_Pages[i][0] != 'p')
			{
				temp_Pages[i][0] = 'h';
				break;
			}
		}
		No_of_Liked_Pages = i;

		tempLikedPages[counter] = new char* [i + 1];

		for (int a = 0; a < i; a++)
		{
			tempLikedPages[counter][a] = Helper::GetStringFromBuffer(temp_Pages[a]);
		}
		counter++;
	}
	
	void Set_ID(char* _ID)
	{
		ID = Helper::GetStringFromBuffer(_ID);
	}

	static void Set_No_of_Users(int _No_of_Users)
	{
		No_of_Users = _No_of_Users;
	}

	static int Get_No_of_Users()
	{
		return No_of_Users;
	}

	int Get_No_of_Friends()
	{
		return No_of_Friends;
	}

	int Get_No_of_Liked_Pages()
	{
		return No_of_Liked_Pages;
	}

	void Set_FirstName(char* _FirstName)
	{
		FirstName = Helper::GetStringFromBuffer(_FirstName);
	}

	char* Get_FirstName()
	{
		return FirstName;
	}

	void Set_LastName(char* _LastName)
	{
		LastName = Helper::GetStringFromBuffer(_LastName);
	}

	char* Get_LastName()
	{
		return LastName;
	}

	void Set_Friend(User* Friend, int counter)
	{
		if (counter == 0)
		{
			FriendList = new User * [No_of_Friends + 1];
		}
		FriendList[counter] = new User;
		char* temp;
		temp = Friend->ID;
		FriendList[counter]->ID = Helper::GetStringFromBuffer(temp);
		temp = Friend->FirstName;
		FriendList[counter]->FirstName = Helper::GetStringFromBuffer(temp);
		temp = Friend->LastName;
		FriendList[counter]->LastName = Helper::GetStringFromBuffer(temp);

	}

	void Set_Page(Page* page, int counter)
	{
		if (counter == 0)
		{
			LikedPages = new Page * [No_of_Liked_Pages];
		}
		
		LikedPages[counter] = new Page;
		
		char* tempID= Helper::GetStringFromBuffer(page->Get_ID());
		LikedPages[counter]->Set_ID(tempID);
		char* tempTitle = Helper::GetStringFromBuffer(page->Get_Title());
		LikedPages[counter]->Set_Title(tempTitle);

	}

	void PrintID()
	{
		cout << ID << " ";
	}

	void PrintFirstName()
	{
		cout << FirstName << " ";
	}

	void PrintLastName()
	{
		cout << LastName << " ";
	}

	User* SearchUser_ID(User** UsersList,const char FriendID[])
	{
		int TotalUsers = User::Get_No_of_Users();
		for (int i = 0; i < TotalUsers; i++)
		{
			char* tempID = new char[5];
			tempID = UsersList[i]->Get_ID();
			
			if (tempID[0] == FriendID[0] && Helper::StringLenght(tempID) == Helper::StringLenght(FriendID))
			{
				int counter = 0;
				for (int j = 0; j < Helper::StringLenght(tempID); j++)
				{
					if (tempID[j] != FriendID[j])
					{
						break;
					}
					counter++;
					if (counter == Helper::StringLenght(FriendID))
					{
						return UsersList[i];
					}

				}

			}
		}
		return nullptr;
	}

	Page* SearchPage_ID(Page** PagesList, char PageID[])
	{
		int TotalPages = Page::Get_TotalPages();
		for (int i = 0; i < TotalPages; i++)
		{
			char* tempID = PagesList[i]->Get_ID();
			if (tempID[0] == PageID[0] && Helper::StringLenght(tempID) == Helper::StringLenght(PageID))
			{
				int counter = 0;
				int Length = Helper::StringLenght(tempID);
				for (int j = 0; j < Length; j++)
				{
					if (tempID[j] != PageID[j])
					{
						break;
					}
					counter++;
					if (counter == Helper::StringLenght(PageID))
					{
						return PagesList[i];
					}
				}

			}
		}
		return nullptr;
	}

	void PrintFriends()
	{
		for (int i = 0; i < No_of_Friends; i++)
		{
			FriendList[i]->PrintID();
			FriendList[i]->PrintFirstName();
			FriendList[i]->PrintLastName();
			cout << endl;
		}
		cout << endl << "----------------------------------------------" << endl;
	}

	void ViewFriendList()
	{
		cout << "----------------------------------------------" << endl;
		cout << "Command: \t" << "View Friend List" << endl;
		cout << "----------------------------------------------" << endl;

		this->PrintFirstName();
		this->PrintLastName();
		cout << " ---- Friend List" << endl << endl;
		PrintFriends();
	}

	void PrintPages()
	{
		for (int i = 0; i < No_of_Liked_Pages; i++)
		{
			cout<<LikedPages[i]->Get_ID();
			cout<<LikedPages[i]->Get_Title();
			cout << endl;
		}
		cout << "-----------------------------------------------" << endl;
	}

	void ViewLikedPages()
	{
		cout << "Command: \t" << "View Liked Pages " << endl;
		cout << "----------------------------------------------" << endl;
		this->PrintFirstName();
		this->PrintLastName();
		cout <<  " ---- Liked Pages" << endl << endl;
		PrintPages();
	}

	~User()
	{
		if (FirstName != nullptr)
		{
			delete FirstName;
		}
		if (LastName != nullptr)
		{
			delete LastName;
		}

		/*for (int i = 0; i < No_of_Friends; i++)
		{
			if (FriendList[i] != nullptr)
			{
				delete FriendList[i];
			}
		}*/
		/*if (FriendList)
		{
			delete[] FriendList;
		}*/

		/*for (int i = 0; i < No_of_Liked_Pages; i++)
		{
			if (LikedPages[i] != nullptr)
			{
				delete LikedPages[i];
			}
		}
		if(LikedPages)
		{
			delete[] LikedPages;
		}*/

	}
};
//Static No of Users
int User::No_of_Users = 0;
//Facebook Class which is basically the controlling class and all the functionalities held through it
class Facebook
{
	User** UsersList;
	Page** PagesList;
	char*** tempFriendList;
	char*** tempLikedPages;
	Page* SearchPageByID;
	User* SearchUserByID;
	Post** PostsList;
	User* CurrentUser;
	int _No_of_Comments;
	Comment** CommentList;
	int PostType;
public:

	Facebook()
	{
		PostType = 0;
		UsersList = 0;
		tempFriendList = nullptr;
		tempLikedPages = nullptr;
		PagesList = 0;
		SearchPageByID = 0;
		SearchUserByID = 0;
		CurrentUser = 0;
		CommentList = 0;
		PostsList = 0;
		_No_of_Comments = 0;
	}

	void Load_Users_Data()
	{
		ifstream Userfile("Users.txt");
		int _No_of_Users;
		Userfile >> _No_of_Users;
		User::Set_No_of_Users(_No_of_Users);
		UsersList = new User * [_No_of_Users];

		tempFriendList = new char** [_No_of_Users];
		tempLikedPages = new char** [_No_of_Users];

		for (int i = 0; i < _No_of_Users; i++)
		{
			UsersList[i] = new User;
			UsersList[i]->LoadDataFromFile(Userfile, tempFriendList, tempLikedPages);
		}
		Userfile.close();
	}

	void Load_Pages_Data()
	{
		ifstream Pagefile("Pages.txt");
		int No_of_Pages;
		Pagefile >> No_of_Pages;
		Page::Set_TotalPages(No_of_Pages);
		PagesList = new Page * [No_of_Pages];
		for (int i = 0; i < No_of_Pages; i++) {
			PagesList[i] = new Page;
			PagesList[i]->LoadDataFromFile(Pagefile);
		}
		Pagefile.close();
	}

	void Load_Posts_Data()
	{
		ifstream Postfile("Post.txt");

		int _No_of_Posts;
		Postfile >> _No_of_Posts;
		cout << _No_of_Posts << "\n";

		Post::Set_No_of_Posts(_No_of_Posts);

		PostsList = new Post * [_No_of_Posts];

		for (int i = 0; i < _No_of_Posts; i++)
		{
			Postfile >> PostType;
			cout << PostType << " ";
			if (PostType == 1)
			{
				PostsList[i] = new Post;
			}
			if (PostType == 2)
			{
				PostsList[i] = new Activity;
			}

			PostsList[i]->LoadDataFromFile(Postfile);

			char* _SharedByID=new char[10];
			Postfile >> _SharedByID;

			Object* tempSharedBy=new Object;
			if (_SharedByID[0] == 'u')
			{
				tempSharedBy = SearchUserByID->SearchUser_ID(UsersList,_SharedByID);
			}
			else if (_SharedByID[0] == 'p')
			{
				tempSharedBy = SearchUserByID->SearchPage_ID(PagesList, _SharedByID);
			}

			PostsList[i]->Set_Posted_By(tempSharedBy);


			char** tempIDs=new char*[20];
			int counter = 0;
			bool Check_for_p = true;
			bool Check_for_u = true;
			while (Check_for_p || Check_for_u)
			{
				tempIDs[counter] = new char[4];
				Postfile >> tempIDs[counter];
				if (tempIDs[counter][0] != 'p' && tempIDs[counter][0] != 'u')
				{
					Check_for_p = false;
					Check_for_u = false;
				}
				counter++;
			}

			if (counter > 0)
			{
				PostsList[i]->No_of_Liked_By(counter - 1);
			}
			

			for (int k = 0; k < counter - 1; k++)
			{
				Object* tempLikedBy = new Object;
				if (tempIDs[k][0] == 'u')
				{
					tempLikedBy = SearchUserByID->SearchUser_ID(UsersList, tempIDs[k]);
				}
				else if (tempIDs[k][0] == 'p')
				{
					tempLikedBy = SearchUserByID->SearchPage_ID(PagesList, tempIDs[k]);
				}

				PostsList[i]->Set_LikedBy(tempLikedBy);

				tempSharedBy->Add_Post(PostsList[i]);
			}
		}
		Postfile.close();
	}

	Post* SearchPostByID(char*  _PostID)
	{
		int TotalPosts = Post::Get_No_of_Posts();
		for (int i = 0; i < TotalPosts; i++)
		{
			char* tempID = new char[5];
			tempID = PostsList[i]->Get_ID();

			if (tempID[0] == _PostID[0] && Helper::StringLenght(tempID) == Helper::StringLenght(_PostID))
			{
				int counter = 0;
				for (int j = 0; j < Helper::StringLenght(tempID); j++)
				{
					if (tempID[j] != _PostID[j])
					{
						break;
					}
					counter++;
					if (counter == Helper::StringLenght(_PostID))
					{
						return PostsList[i];
					}
				}

			}
		}
		return nullptr;
	}

	void Load_Comments_Data()
	{
		cout << endl << endl << "Loading Comments" << endl << endl;
		ifstream Commentfile("comment.txt");
		
		Commentfile >> _No_of_Comments;
		cout << _No_of_Comments << endl;

		CommentList = new Comment * [_No_of_Comments];
		for (int i = 0; i < _No_of_Comments; i++)
		{
			CommentList[i] = new Comment;
			
			char* _CommentID = new char[4];
			Commentfile >> _CommentID;
			CommentList[i]->Set_ID(_CommentID);
			cout<<CommentList[i]->Get_ID() << endl;


			char* tempPostID = new char[10];
			Commentfile >> tempPostID;

			Post* tempID_Post = new Post;
			tempID_Post = SearchPostByID(tempPostID);

			char* _temp_SharedByID = new char[4];
			Object* _tempObject = new Object;
			Commentfile >> _temp_SharedByID;
			if (_temp_SharedByID[0] == 'u')
			{
				_tempObject = SearchUserByID->SearchUser_ID(UsersList, _temp_SharedByID);
				CommentList[i]->Set_CommentedBy(_tempObject);
			}
			else if (_temp_SharedByID[0] == 'p')
			{
				_tempObject = SearchUserByID->SearchPage_ID(PagesList, _temp_SharedByID);
				CommentList[i]->Set_CommentedBy(_tempObject);
			}

			char* temp_Text = new char[150];

			Commentfile.getline(temp_Text,150);
			CommentList[i]->Set_Text(temp_Text);
			cout << CommentList[i]->Get_Text() << endl;;

			tempID_Post->Add_Comment(*CommentList[i]);


		}

	}

	void AssociateFriends()
	{
		int TotalUsers = User::Get_No_of_Users();
		for (int i = 0; i < TotalUsers; i++)
		{
			int TotalFriends = UsersList[i]->Get_No_of_Friends();
			for (int j = 0; j < TotalFriends; j++)
			{
				char* Friend_ID = tempFriendList[i][j];

				SearchUserByID = new User;
				SearchUserByID = UsersList[i]->SearchUser_ID(UsersList,Friend_ID);
				if (SearchUserByID!=nullptr)
				{
					UsersList[i]->Set_Friend(SearchUserByID, j);
				}
			}
		}
	}

	void AssociatePages()
	{
		int TotalUsers = User::Get_No_of_Users();
		for (int i = 0; i < TotalUsers; i++)
		{
			int TotalLikedPages = UsersList[i]->Get_No_of_Liked_Pages();
			for (int j = 0; j < TotalLikedPages; j++)
			{
				//char* Page_ID = tempLikedPages[i][j];

				SearchPageByID = new Page;
				SearchPageByID = UsersList[i]->SearchPage_ID(PagesList, tempLikedPages[i][j]);
				if (SearchPageByID != nullptr)
				{
					UsersList[i]->Set_Page(SearchPageByID, j);
				}
			}
		}
	}

	bool SetCurrentUser(const char user[])
	{
		CurrentUser = UsersList[0]->SearchUser_ID(UsersList,user);
		if (CurrentUser != nullptr)
		{
			CurrentUser->PrintFirstName();
			CurrentUser->PrintLastName();
			cout << "successfully set as Current User" << endl << endl;
			return true;
		}
		else
		{
			cout << "User Not Found!!!" << endl;
			return false;
		}
	}

	void Run()
	{
		CurrentUser->ViewFriendList();
		CurrentUser->ViewLikedPages();
		//CurrentUser->ViewHome();
	}

	~Facebook()
	{
		int TotalUsers = User::Get_No_of_Users();
		for (int i = 0; i < TotalUsers; i++)
		{
			int TotalFriends = UsersList[i]->Get_No_of_Friends();
			for (int j = 0; j < TotalFriends; j++)
			{
				delete tempFriendList[i][j];
			}
			int TotalLikedPages = UsersList[i]->Get_No_of_Liked_Pages();
			for (int j = 0; j < TotalLikedPages; j++)
			{
				delete tempLikedPages[i][j];
			}
		}
		delete[] tempFriendList;
		delete[] tempLikedPages;

		for (int i = 0; i < TotalUsers; i++)
		{
			delete UsersList[i];
		}
		delete [] UsersList;

	}

};

void main()
{
	Facebook facebook;
	facebook.Load_Users_Data();
	facebook.Load_Pages_Data();
	facebook.Load_Posts_Data();
	facebook.Load_Comments_Data();
	facebook.AssociateFriends();
	facebook.AssociatePages();
	if (facebook.SetCurrentUser("u7"))
	{
		facebook.Run();
		system("pause");
	}

	system("pause");

}