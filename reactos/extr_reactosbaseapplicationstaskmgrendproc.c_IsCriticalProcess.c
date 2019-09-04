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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtQueryInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessBreakOnTermination ; 
 int /*<<< orphan*/  TRUE ; 

BOOL IsCriticalProcess(HANDLE hProcess)
{
    NTSTATUS status;
    ULONG BreakOnTermination;

    /* return early if the process handle does not exist */
    if (!hProcess)
        return FALSE;

    /* the important system processes that we don't want to let the user
       kill come marked as critical, this simplifies the check greatly.

       a critical process brings the system down when is terminated:
       <http://www.geoffchappell.com/studies/windows/win32/ntdll/api/rtl/peb/setprocessiscritical.htm> */

    status = NtQueryInformationProcess(hProcess,
                                       ProcessBreakOnTermination,
                                       &BreakOnTermination,
                                       sizeof(ULONG),
                                       NULL);

    if (NT_SUCCESS(status) && BreakOnTermination)
        return TRUE;

    return FALSE;
}