#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetDiskFreeSpaceEx (int /*<<< orphan*/  const*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
DiskFreeMain(int argc, const TCHAR *argv[])
{
    ULARGE_INTEGER FreeAvail, TotalNumber, TotalNumberFree;

    /* We need a path */
    if (argc < 2)
    {
        _ftprintf(stderr, _T("Usage: fsutil volume diskfree <volume path>\n"));
        _ftprintf(stderr, _T("\tFor example: fsutil volume diskfree c:\n"));
        return 1;
    }

    if (!GetDiskFreeSpaceEx(argv[1], &FreeAvail, &TotalNumber, &TotalNumberFree))
    {
        PrintErrorMessage(GetLastError());
        return 1;
    }

    _ftprintf(stdout, _T("Total free bytes\t\t: %I64i\n"), TotalNumberFree.QuadPart);
    _ftprintf(stdout, _T("Total bytes\t\t\t: %I64i\n"), TotalNumber.QuadPart);
    _ftprintf(stdout, _T("Total free available bytes\t: %I64i\n"), FreeAvail.QuadPart);

    return 0;
}