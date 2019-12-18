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
typedef  int* LPCWSTR ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateShellLink (int*,int*,char*,int*,int*,int,int*) ; 
 scalar_t__ ExpandEnvironmentStringsW (int*,int*,scalar_t__) ; 
 scalar_t__ GetFullPathNameW (int*,scalar_t__,int*,int**) ; 
 int MAX_PATH ; 
 int* PathAddBackslash (int*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int*,int*) ; 

__attribute__((used)) static BOOL
CreateShortcut(
    LPCWSTR pszFolder,
    LPCWSTR pszName,
    LPCWSTR pszCommand,
    LPCWSTR pszDescription,
    INT iIconNr,
    LPCWSTR pszWorkingDir)
{
    DWORD dwLen;
    LPWSTR Ptr;
    LPWSTR lpFilePart;
    WCHAR szPath[MAX_PATH];
    WCHAR szWorkingDirBuf[MAX_PATH];

    /* If no working directory is provided, try to compute a default one */
    if (pszWorkingDir == NULL || pszWorkingDir[0] == L'\0')
    {
        if (ExpandEnvironmentStringsW(pszCommand, szPath, ARRAYSIZE(szPath)) == 0)
            wcscpy(szPath, pszCommand);

        dwLen = GetFullPathNameW(szPath,
                                 ARRAYSIZE(szWorkingDirBuf),
                                 szWorkingDirBuf,
                                 &lpFilePart);
        if (dwLen != 0 && dwLen <= ARRAYSIZE(szWorkingDirBuf))
        {
            /* Since those should only be called with (.exe) files,
               lpFilePart has not to be NULL */
            ASSERT(lpFilePart != NULL);

            /* We're only interested in the path. Cut the file name off.
               Also remove the trailing backslash unless the working directory
               is only going to be a drive, i.e. C:\ */
            *(lpFilePart--) = L'\0';
            if (!(lpFilePart - szWorkingDirBuf == 2 &&
                  szWorkingDirBuf[1] == L':' && szWorkingDirBuf[2] == L'\\'))
            {
                *lpFilePart = L'\0';
            }
            pszWorkingDir = szWorkingDirBuf;
        }
    }

    /* If we failed to compute a working directory, just do not use one */
    if (pszWorkingDir && pszWorkingDir[0] == L'\0')
        pszWorkingDir = NULL;

    /* Build the shortcut file name */
    wcscpy(szPath, pszFolder);
    Ptr = PathAddBackslash(szPath);
    wcscpy(Ptr, pszName);

    /* Create the shortcut */
    return SUCCEEDED(CreateShellLink(szPath,
                                     pszCommand,
                                     L"",
                                     pszWorkingDir,
                                     /* Special value to indicate no icon */
                                     (iIconNr != -1 ? pszCommand : NULL),
                                     iIconNr,
                                     pszDescription));
}