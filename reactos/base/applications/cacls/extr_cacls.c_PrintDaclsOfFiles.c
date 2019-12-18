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
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_NO_MORE_FILES ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ FindNextFile (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetPathOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OptionC ; 
 int /*<<< orphan*/  PrintError (scalar_t__) ; 
 int /*<<< orphan*/  PrintFileDacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
PrintDaclsOfFiles(LPCTSTR pszFiles)
{
    TCHAR FilePath[MAX_PATH];
    WIN32_FIND_DATA FindData;
    HANDLE hFind;
    DWORD LastError;

    /*
     * get the file path
     */
    if (!GetPathOfFile(FilePath, pszFiles))
        return FALSE;

    /*
     * search for the files
     */
    hFind = FindFirstFile(pszFiles, &FindData);
    if (hFind == INVALID_HANDLE_VALUE)
        return FALSE;

    do
    {
        if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        if (!PrintFileDacl(FilePath, FindData.cFileName))
        {
            LastError = GetLastError();
            if (LastError == ERROR_ACCESS_DENIED)
            {
                PrintError(LastError);
                if (!OptionC)
                {
                    FindClose(hFind);
                    return FALSE;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            ConPuts(StdOut, L"\n");
        }
    } while(FindNextFile(hFind, &FindData));
    LastError = GetLastError();
    FindClose(hFind);

    if (LastError != ERROR_NO_MORE_FILES)
    {
        PrintError(LastError);
        return FALSE;
    }

    return TRUE;
}