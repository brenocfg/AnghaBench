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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* PCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int ENABLE_ECHO_INPUT ; 
 int ENABLE_LINE_INPUT ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InputCodePage ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZeroMemory (scalar_t__*,int) ; 
 scalar_t__ _T (char) ; 
 scalar_t__ cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (scalar_t__*) ; 

VOID ConInString(LPTSTR lpInput, DWORD dwLength)
{
    DWORD dwOldMode;
    DWORD dwRead = 0;
    HANDLE hFile;

    LPTSTR p;
    PCHAR pBuf;

#ifdef _UNICODE
    pBuf = (PCHAR)cmd_alloc(dwLength - 1);
#else
    pBuf = lpInput;
#endif
    ZeroMemory(lpInput, dwLength * sizeof(TCHAR));
    hFile = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hFile, &dwOldMode);

    SetConsoleMode(hFile, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    ReadFile(hFile, (PVOID)pBuf, dwLength - 1, &dwRead, NULL);

#ifdef _UNICODE
    MultiByteToWideChar(InputCodePage, 0, pBuf, dwRead, lpInput, dwLength - 1);
    cmd_free(pBuf);
#endif
    for (p = lpInput; *p; p++)
    {
        if (*p == _T('\x0d'))
        {
            *p = _T('\0');
            break;
        }
    }

    SetConsoleMode(hFile, dwOldMode);
}