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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PCHAR ;
typedef  int* LPWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_OEMCP ; 
 int ENABLE_ECHO_INPUT ; 
 int ENABLE_LINE_INPUT ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int*,int) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZeroMemory (int*,int) ; 

VOID
ReadFromConsole(
    LPWSTR lpInput,
    DWORD dwLength,
    BOOL bEcho)
{
    DWORD dwOldMode;
    DWORD dwRead = 0;
    HANDLE hFile;
    LPWSTR p;
    PCHAR pBuf;

    pBuf = HeapAlloc(GetProcessHeap(), 0, dwLength - 1);
    ZeroMemory(lpInput, dwLength * sizeof(WCHAR));
    hFile = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hFile, &dwOldMode);

    SetConsoleMode(hFile, ENABLE_LINE_INPUT | (bEcho ? ENABLE_ECHO_INPUT : 0));

    ReadFile(hFile, (PVOID)pBuf, dwLength - 1, &dwRead, NULL);

    MultiByteToWideChar(CP_OEMCP, 0, pBuf, dwRead, lpInput, dwLength - 1);
    HeapFree(GetProcessHeap(), 0, pBuf);

    for (p = lpInput; *p; p++)
    {
        if (*p == L'\x0d')
        {
            *p = L'\0';
            break;
        }
    }

    SetConsoleMode(hFile, dwOldMode);
}