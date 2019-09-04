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
typedef  scalar_t__ TCHAR ;
typedef  size_t INT_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectory (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__* _tcschr (scalar_t__*,scalar_t__) ; 
 int _tcslen (scalar_t__*) ; 
 int /*<<< orphan*/  _tcsncpy (scalar_t__*,scalar_t__*,size_t) ; 

BOOL
MakeFullPath(TCHAR * DirPath)
{
    TCHAR path[MAX_PATH];
    TCHAR *p = DirPath;
    INT_PTR  n;

    if (CreateDirectory(DirPath, NULL))
        return TRUE;
    else if (GetLastError() != ERROR_PATH_NOT_FOUND)
        return FALSE;

    /* got ERROR_PATH_NOT_FOUND, so try building it up one component at a time */
    if (p[0] && p[1] == _T(':'))
        p += 2;
    while (*p == _T('\\'))
        p++; /* skip drive root */
    do
    {
        p = _tcschr(p, _T('\\'));
        n = p ? p++ - DirPath : _tcslen(DirPath);
        _tcsncpy(path, DirPath, n);
        path[n] = _T('\0');
        if ( !CreateDirectory(path, NULL) &&
            (GetLastError() != ERROR_ALREADY_EXISTS))
        {
            return FALSE;
        }
    } while (p != NULL);

    return TRUE;
}