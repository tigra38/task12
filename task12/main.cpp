#include <string>
#include <iostream>
using namespace std;

#define NO_OF_CHARS 256  
#define debug true

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS])
{
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
    {
        badchar[(int)str[i]] = i;
    }

    if (debug)
    {
        cout << "BadHeuristic Table: " << endl;

        for (i = 0; i < NO_OF_CHARS; i++)
        {
            if (i % 16 == 0) cout << i << ": ";
            cout << badchar[i] << " ";
            if (i % 16 == 15) cout << endl;
        }

        cout << "end" << endl;
    }

}

/*void search(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();

    cout << m << "-" << n << endl;

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            cout << "pattern occurs at shift = " << s << endl;

            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        }
        else
        {
            int bc = badchar[txt[s + j]];
            s += max(1, j - bc);
        }
    }
}*/

int search_K(string txt, string pat)
{
    int match = 0;
    int m = pat.size();
    int n = txt.size();

    if (debug) cout << "pat size: " << m << ", txt size: " << n << endl;

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            if (debug) cout << "pattern occurs at shift = " << s << endl;
            match++;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        }
        else
        {
            int bc = badchar[txt[s + j]];
            s += max(1, j - bc);
        }
    }
    return match;
}

bool FoundNonPeriodic(string txt, int K)
{
    for (int i = 0; i < txt.size(); i++) cout << txt[i];
    cout << endl;

    if (txt.size() % K != 0)
    {
        cout << "Incorrect size" << endl;
        //return false;
    }
    for (int i = 1; i < txt.size() / K; i++) {
        for (int j = 0; j < K; j++) {
            if (txt[(K * (i - 1) + j)] != txt[(K * i) + j])
            {
                cout << "^";
                for (int l = 0; l < K - 1; l++) cout << " ";
                cout << "^ Non-periodic symbol (" << K * i + j << ")" << endl;
                return false;
            }
            cout << " ";
        }
    }
    return true;
}

bool IsKPeriodic(string txt, int K)
{
    string pat = txt.substr(0, K);
    if (txt.size() % K != 0)
    {
        if (debug) cout << "incorrect size!" << endl;
        return false;
    }
    if (search_K(txt, pat) != txt.size() / K)
    {
        if (debug) FoundNonPeriodic(txt, K);
        return false;
    }
    return true;
}

int main()
{
    std::string test = "abcdefghabcdefghabcdefghabceefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh";
    if (IsKPeriodic(test, 8)) {
        cout << "String is periodic" << endl;
    }
    else cout << "String is not periodic!" << endl;
    return 0;
}