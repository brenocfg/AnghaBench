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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FSCTL_DISMOUNT_VOLUME ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ LockOrUnlockVolume (scalar_t__,scalar_t__) ; 
 scalar_t__ OpenVolume (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
DismountMain(int argc, const TCHAR *argv[])
{
    HANDLE Volume;
    ULONG BytesRead;

    /* We need a volume (letter or GUID) */
    if (argc < 2)
    {
        _ftprintf(stderr, _T("Usage: fsutil volume dismount <volume>\n"));
        _ftprintf(stderr, _T("\tFor example: fsutil volume dismount d:\n"));
        return 1;
    }

    /* Get a handle for the volume */
    Volume = OpenVolume(argv[1], FALSE, FALSE);
    if (Volume == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    /* Attempt to lock the volume */
    if (LockOrUnlockVolume(Volume, TRUE))
    {
        CloseHandle(Volume);
        return 1;
    }

    /* Issue the dismount command */
    if (DeviceIoControl(Volume, FSCTL_DISMOUNT_VOLUME, NULL, 0, NULL,
                        0, &BytesRead, NULL) == FALSE)
    {
        PrintErrorMessage(GetLastError());
        LockOrUnlockVolume(Volume, FALSE);
        CloseHandle(Volume);
        return 1;
    }

    /* Unlock and quit */
    LockOrUnlockVolume(Volume, FALSE);
    CloseHandle(Volume);

    _ftprintf(stdout, _T("The %s volume has been dismounted\n"), argv[1]);

    return 0;
}