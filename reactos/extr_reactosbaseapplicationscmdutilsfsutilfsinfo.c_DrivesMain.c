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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
DrivesMain(int argc, const TCHAR *argv[])
{
    UINT i;
    DWORD Drives;

    /* Get the drives bitmap */
    Drives = GetLogicalDrives();
    if (Drives == 0)
    {
        PrintErrorMessage(GetLastError());
        return 1;
    }

    /* And output any found drive */
    _ftprintf(stdout, _T("Drives:"));
    for (i = 0; i < 26; i++)
    {
        if (Drives & (1 << i))
        {
            _ftprintf(stdout, _T(" %c:\\"), 'A' + i);
        }
    }
    _ftprintf(stdout, _T("\n"));

    return 0;
}