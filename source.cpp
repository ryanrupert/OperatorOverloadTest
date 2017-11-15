/**
* Created by Ryan Rupert
* Date: 2017-11-15
* Source: None
* This is a test of how operator overloading
*/

#include <iostream>
#include <map>

class Test
{
	public:
		//Source: http://www.cplusplus.com/forum/beginner/64186/
		friend std::istream& operator >> (std::istream & in, Test& i);
		friend std::ostream& operator << (std::ostream & out, Test& o);
		Test& operator ++();
	private:
		enum Status { TEST, TEST2, TEST3, TEST4 };
		Status status;
		//Source: https://stackoverflow.com/a/10514661
		std::map<std::string, Test::Status> m = { {"Test", TEST}, {"Test2", TEST2}, {"Test3", TEST3}, {"Test4", TEST4} };
};

std::istream& operator >> (std::istream & in, Test& i)
{
	std::string temp;
	in >> temp;
	in.get();
	//Source: https://stackoverflow.com/a/10514661
	i.status = i.m[temp];
	return in;
}

std::ostream& operator << (std::ostream & out, Test& o)
{
	std::string temp;
	//Source: https://github.com/ryanrupert/StraddlingCheckerboards/blob/3479ccb785481f1bc0aaa28c2311e139ee827843/src/Maps.cpp
	//the for const auto loop at the above link
	for(const auto& foo : o.m)
	{
		if (foo.second == o.status) 
		{
			temp = foo.first;
			break;
		}
	}
	out << temp;
	return out;
}

Test& Test::operator ++()
{
	status = static_cast<Status>(status + 1);
	return *this;
}

int main()
{
	Test test;
	std::cout << "Please enter a value:" << std::endl;
	std::cin >> test;
	std::cout << "You entered: " << test << std::endl;
	std::cin.get();
	return 0;
}
