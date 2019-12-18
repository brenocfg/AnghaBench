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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetConsoleOutputCP () ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WriteConsoleW (int /*<<< orphan*/ ,char const*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int strlenW (char const*) ; 
 scalar_t__ wshInteractive ; 

__attribute__((used)) static void print_string(const WCHAR *string)
{
    DWORD count, ret, len, lena;
    char *buf;

    if(wshInteractive) {
        static const WCHAR windows_script_hostW[] =
            {'W','i','n','d','o','w','s',' ','S','c','r','i','p','t',' ','H','o','s','t',0};
        MessageBoxW(NULL, string, windows_script_hostW, MB_OK);
        return;
    }

    len = strlenW(string);
    ret = WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), string, len, &count, NULL);
    if(ret) {
        static const WCHAR crnlW[] = {'\r','\n'};
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), crnlW, ARRAY_SIZE(crnlW), &count, NULL);
        return;
    }

    lena = WideCharToMultiByte(GetConsoleOutputCP(), 0, string, len, NULL, 0, NULL, NULL);
    buf = heap_alloc(len);
    if(!buf)
        return;

    WideCharToMultiByte(GetConsoleOutputCP(), 0, string, len, buf, lena, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, lena, &count, FALSE);
    heap_free(buf);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), "\r\n", 2, &count, FALSE);
}