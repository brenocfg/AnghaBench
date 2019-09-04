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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  EnumDependentServices (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenServiceW (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int SERVICE_ENUMERATE_DEPENDENTS ; 
 int SERVICE_QUERY_STATUS ; 
 int /*<<< orphan*/  SERVICE_STATE_ALL ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
TV2_HasDependantServices(LPWSTR lpServiceName)
{
    HANDLE hSCManager;
    HANDLE hService;
    DWORD dwBytesNeeded, dwCount;
    BOOL bRet = FALSE;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (hSCManager)
    {
        hService = OpenServiceW(hSCManager,
                                lpServiceName,
                                SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);
        if (hService)
        {
            /* Does this have any dependencies? */
            if (!EnumDependentServices(hService,
                                       SERVICE_STATE_ALL,
                                       NULL,
                                       0,
                                       &dwBytesNeeded,
                                       &dwCount))
            {
                 if (GetLastError() == ERROR_MORE_DATA)
                 {
                     /* It does, return TRUE */
                     bRet = TRUE;
                 }
            }

            CloseServiceHandle(hService);
        }

        CloseServiceHandle(hSCManager);
    }

    return bRet;
}