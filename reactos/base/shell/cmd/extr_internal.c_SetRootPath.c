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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrFormatMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetFullPathName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetPathCase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetCurrentDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripQuotes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _tchdir (int /*<<< orphan*/ *) ; 
 scalar_t__ _tcsncicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nErrorLevel ; 

BOOL SetRootPath(TCHAR *oldpath, TCHAR *InPath)
{
    TCHAR OutPath[MAX_PATH];
    TCHAR OutPathTemp[MAX_PATH];

    StripQuotes(InPath);

    /* Retrieve the full path name from the (possibly relative) InPath */
    if (GetFullPathName(InPath, MAX_PATH, OutPathTemp, NULL) == 0)
        goto Fail;

    /* Convert the full path to its correct case.
     * Example: c:\windows\SYSTEM32 => C:\WINDOWS\System32 */
    GetPathCase(OutPathTemp, OutPath);

    /* Use _tchdir, since unlike SetCurrentDirectory it updates
     * the current-directory-on-drive environment variables. */
    if (_tchdir(OutPath) != 0)
        goto Fail;

    /* Keep original drive in ordinary CD/CHDIR (without /D switch). */
    if (oldpath != NULL && _tcsncicmp(OutPath, oldpath, 2) != 0)
        SetCurrentDirectory(oldpath);

    return TRUE;

Fail:
    ConErrFormatMessage(GetLastError());
    nErrorLevel = 1;
    return FALSE;
}