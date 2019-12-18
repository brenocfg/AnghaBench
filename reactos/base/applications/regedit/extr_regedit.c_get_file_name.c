#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int WCHAR ;
typedef  int* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getAppName () ; 
 scalar_t__ iswspace (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

void get_file_name(LPWSTR *command_line, LPWSTR file_name)
{
    WCHAR *s = *command_line;
    size_t pos = 0; /* position of pointer "s" in *command_line */
    file_name[0] = 0;

    if (!s[0])
    {
        return;
    }

    if (s[0] == L'"')
    {
        s++;
        (*command_line)++;
        while(s[0] != L'"')
        {
            if (!s[0])
            {
                fwprintf(stderr, L"%s: Unexpected end of file name!\n", getAppName());
                exit(1);
            }
            s++;
            pos++;
        }
    }
    else
    {
        while(s[0] && !iswspace(s[0]))
        {
            s++;
            pos++;
        }
    }
    memcpy(file_name, *command_line, pos * sizeof(WCHAR));
    /* remove the last backslash */
    if (file_name[pos - 1] == L'\\')
    {
        file_name[pos - 1] = L'\0';
    }
    else
    {
        file_name[pos] = L'\0';
    }

    if (s[0])
    {
        s++;
        pos++;
    }
    while(s[0] && iswspace(s[0]))
    {
        s++;
        pos++;
    }
    (*command_line) += pos;
}