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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FSCTL_LOCK_VOLUME ; 
 int /*<<< orphan*/  FSCTL_UNLOCK_VOLUME ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
LockOrUnlockVolume(HANDLE Volume, BOOLEAN Lock)
{
    DWORD Operation;
    ULONG BytesRead;

    Operation = (Lock ? FSCTL_LOCK_VOLUME : FSCTL_UNLOCK_VOLUME);
    if (DeviceIoControl(Volume, Operation, NULL, 0, NULL, 0,
                        &BytesRead, NULL) == FALSE)
    {
        PrintErrorMessage(GetLastError());
        return 1;
    }

    return 0;
}