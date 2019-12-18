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
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  OpenService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVICE_ALL_ACCESS ; 
 int /*<<< orphan*/  StartService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitForService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
StartAudioService(
    SC_HANDLE hSCManager,
    LPWSTR ServiceName,
    ULONG RetryCount)
{
    SC_HANDLE hService;
    BOOL ret;

    hService = OpenService(hSCManager, ServiceName, SERVICE_ALL_ACCESS);
    if (!hService)
    {
        logmsg("Failed to open service %S %x\n", ServiceName, GetLastError());
        return FALSE;
    }

    if (!StartService(hService, 0, NULL))
    {
        logmsg("Failed to start service %S %x\n", ServiceName, GetLastError());
        CloseServiceHandle(hService);
        return FALSE;
    }

    ret = WaitForService(hService, RetryCount);

    CloseServiceHandle(hService);
    return ret;
}