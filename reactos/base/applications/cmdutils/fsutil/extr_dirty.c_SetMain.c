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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FSCTL_MARK_VOLUME_DIRTY ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ OpenVolume (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
SetMain(int argc, const TCHAR *argv[])
{
    HANDLE Volume;
    DWORD BytesRead;

    /* We need a volume (letter or GUID) */
    if (argc < 2)
    {
        _ftprintf(stderr, _T("Usage: fsutil dirty set <volume>\n"));
        _ftprintf(stderr, _T("\tFor example: fsutil dirty set c:\n"));
        return 1;
    }

    /* Get a handle for the volume */
    Volume = OpenVolume(argv[1], FALSE, FALSE);
    if (Volume == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    /* And set the dirty bit */
    if (DeviceIoControl(Volume, FSCTL_MARK_VOLUME_DIRTY, NULL, 0, NULL, 0, &BytesRead, NULL) == FALSE)
    {
        PrintErrorMessage(GetLastError());
        CloseHandle(Volume);
        return 1;
    }

    CloseHandle(Volume);

    /* Print the status */
    _ftprintf(stdout, _T("The %s volume is now marked as dirty\n"), argv[1]);

    return 0;
}