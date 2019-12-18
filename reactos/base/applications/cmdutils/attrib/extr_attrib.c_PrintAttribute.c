#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/ * cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ErrorMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
INT
PrintAttribute(
    LPWSTR pszPath,
    LPWSTR pszFile,
    BOOL bRecurse)
{
    WIN32_FIND_DATAW findData;
    HANDLE hFind;
    WCHAR  szFullName[MAX_PATH];
    LPWSTR pszFileName;

    /* prepare full file name buffer */
    wcscpy(szFullName, pszPath);
    pszFileName = szFullName + wcslen(szFullName);

    /* display all subdirectories */
    if (bRecurse)
    {
        /* append file name */
        wcscpy(pszFileName, pszFile);

        hFind = FindFirstFileW(szFullName, &findData);
        if (hFind == INVALID_HANDLE_VALUE)
        {
            ErrorMessage(GetLastError(), pszFile);
            return 1;
        }

        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                continue;

            if (!wcscmp(findData.cFileName, L".") ||
                !wcscmp(findData.cFileName, L".."))
                continue;

            wcscpy(pszFileName, findData.cFileName);
            wcscat(pszFileName, L"\\");
            PrintAttribute(szFullName, pszFile, bRecurse);
        }
        while(FindNextFileW(hFind, &findData));
        FindClose(hFind);
    }

    /* append file name */
    wcscpy(pszFileName, pszFile);

    /* display current directory */
    hFind = FindFirstFileW(szFullName, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        ErrorMessage(GetLastError(), pszFile);
        return 1;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        wcscpy(pszFileName, findData.cFileName);

        ConPrintf(StdOut,
                  L"%c  %c%c%c     %s\n",
                  (findData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) ? L'A' : L' ',
                  (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) ? L'S' : L' ',
                  (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? L'H' : L' ',
                  (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? L'R' : L' ',
                  szFullName);
    }
    while(FindNextFileW(hFind, &findData));
    FindClose(hFind);

    return 0;
}