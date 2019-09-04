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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (scalar_t__*) ; 
 int /*<<< orphan*/  ERROR_DIRECTORY ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  GetCurrentDirectory (int,scalar_t__*) ; 
 int GetFileAttributes (scalar_t__*) ; 
 int /*<<< orphan*/  GetFullPathName (scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PrintError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__* _tcsrchr (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyn (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL
GetPathOfFile(LPTSTR FilePath, LPCTSTR pszFiles)
{
    TCHAR FullPath[MAX_PATH];
    LPTSTR pch;
    DWORD attrs;

    lstrcpyn(FilePath, pszFiles, MAX_PATH);
    pch = _tcsrchr(FilePath, _T('\\'));
    if (pch != NULL)
    {
        *pch = 0;
        if (!GetFullPathName(FilePath, MAX_PATH, FullPath, NULL))
        {
            PrintError(GetLastError());
            return FALSE;
        }
        lstrcpyn(FilePath, FullPath, MAX_PATH);

        attrs = GetFileAttributes(FilePath);
        if (attrs == 0xFFFFFFFF || !(attrs & FILE_ATTRIBUTE_DIRECTORY))
        {
            PrintError(ERROR_DIRECTORY);
            return FALSE;
        }
    }
    else
        GetCurrentDirectory(MAX_PATH, FilePath);

    AddBackslash(FilePath);
    return TRUE;
}