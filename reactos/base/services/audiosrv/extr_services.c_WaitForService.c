#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ dwCurrentState; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  QueryServiceStatusEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_STATUS_PROCESS_INFO ; 
 scalar_t__ SERVICE_RUNNING ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  logmsg (char*,int /*<<< orphan*/ ) ; 

BOOL
WaitForService(
    SC_HANDLE hService,
    ULONG RetryCount)
{
    ULONG Index = 0;
    DWORD dwSize;
    SERVICE_STATUS_PROCESS Info;

    do
    {
        if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&Info, sizeof(SERVICE_STATUS_PROCESS), &dwSize))
        {
            logmsg("QueryServiceStatusEx failed %x\n", GetLastError());
            break;
        }

        if (Info.dwCurrentState == SERVICE_RUNNING)
            return TRUE;

        Sleep(1000);

    } while (Index++ < RetryCount);

    logmsg("Timeout while waiting for service to become ready %p\n", hService);

    return FALSE;
}