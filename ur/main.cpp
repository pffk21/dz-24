
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int main()
{
    string file;
    cout << "путь к файлу: ";
    getline(cin, file);
    ifstream in(file);
    if (!in)
    {
        cout << "не открылось: " << file << endl;
        return 1;
    }
    string line;
    int open = 0;
    int close = 0;
    string last_open;
    while (getline(in, line))
      {
          for (int i = 0; i < line.length(); i++)
          {
              if (line[i] == '<')
              {
                  if (i + 1 < line.length() && line[i + 1] == '/')
                  {
                      close++;
                      string close_tag;
                      i += 2;
                      while (i < line.length() && line[i] != '>')
                      {
                          close_tag += line[i];
                          i++;
                      }
                      if (last_open != close_tag)
                      {
                          cout << "тег </" << close_tag << "> не соответствует открытому тегу <" << last_open << ">" << endl;
                          return 1;
                      }
                      last_open = "";
                  }
                  else
                  {
                      open++;
                      string open_tag;
                      i++;
                      while (i < line.length() && line[i] != '>')
                      {
                          open_tag += line[i];
                          i++;
                      }
                      last_open= open_tag;
                  }
              }
          }
      }

    if (open == close)
    {
        cout << "файл валиден" << endl;
    }
    else if (open > close)
    {
        cout << "не хватает > тегов" << endl;
    }
    else
    {
        cout << "не хватает < тегов" << endl;
    }
    in.close();
}
