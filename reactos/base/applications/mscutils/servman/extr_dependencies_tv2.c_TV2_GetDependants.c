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
typedef  scalar_t__ SC_HANDLE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPENUM_SERVICE_STATUSW ;
typedef  int /*<<< orphan*/ * LPENUM_SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ EnumDependentServicesW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenServiceW (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int SERVICE_ENUMERATE_DEPENDENTS ; 
 int SERVICE_QUERY_CONFIG ; 
 int SERVICE_QUERY_STATUS ; 
 int /*<<< orphan*/  SERVICE_STATE_ALL ; 

LPENUM_SERVICE_STATUS
TV2_GetDependants(LPWSTR lpServiceName,
                  LPDWORD lpdwCount)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    LPENUM_SERVICE_STATUSW lpDependencies = NULL;
    DWORD dwBytesNeeded;
    DWORD dwCount;

    /* Set the first items in each tree view */
    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (hSCManager)
    {
        hService = OpenServiceW(hSCManager,
                                lpServiceName,
                                SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_QUERY_CONFIG);
        if (hService)
        {
            /* Does this have any dependencies? */
            if (!EnumDependentServicesW(hService,
                                        SERVICE_STATE_ALL,
                                        NULL,
                                        0,
                                        &dwBytesNeeded,
                                        &dwCount) &&
                GetLastError() == ERROR_MORE_DATA)
            {
                lpDependencies = (LPENUM_SERVICE_STATUSW)HeapAlloc(GetProcessHeap(),
                                                                  0,
                                                                  dwBytesNeeded);
                if (lpDependencies)
                {
                    /* Get the list of dependents */
                    if (EnumDependentServicesW(hService,
                                               SERVICE_STATE_ALL,
                                               lpDependencies,
                                               dwBytesNeeded,
                                               &dwBytesNeeded,
                                               &dwCount))
                    {
                        /* Set the count */
                        *lpdwCount = dwCount;
                    }
                    else
                    {
                        HeapFree(ProcessHeap,
                                 0,
                                 lpDependencies);

                        lpDependencies = NULL;
                    }
                }
            }

            CloseServiceHandle(hService);
        }

        CloseServiceHandle(hSCManager);
    }

    return lpDependencies;
}