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
typedef  int /*<<< orphan*/ * LPQUERY_SERVICE_CONFIGW ;
typedef  int /*<<< orphan*/ * LPQUERY_SERVICE_CONFIG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenServiceW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryServiceConfigW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_QUERY_CONFIG ; 

LPQUERY_SERVICE_CONFIG
GetServiceConfig(LPWSTR lpServiceName)
{
    LPQUERY_SERVICE_CONFIGW lpServiceConfig = NULL;
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    DWORD dwBytesNeeded;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_CONNECT);
    if (hSCManager)
    {
        hService = OpenServiceW(hSCManager,
                                lpServiceName,
                                SERVICE_QUERY_CONFIG);
        if (hService)
        {
            if (!QueryServiceConfigW(hService,
                                     NULL,
                                     0,
                                     &dwBytesNeeded))
            {
                if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                {
                    lpServiceConfig = (LPQUERY_SERVICE_CONFIG)HeapAlloc(GetProcessHeap(),
                                                                        0,
                                                                        dwBytesNeeded);
                    if (lpServiceConfig)
                    {
                        if (!QueryServiceConfigW(hService,
                                                lpServiceConfig,
                                                dwBytesNeeded,
                                                &dwBytesNeeded))
                        {
                            HeapFree(GetProcessHeap(),
                                     0,
                                     lpServiceConfig);
                            lpServiceConfig = NULL;
                        }
                    }
                }
            }

            CloseServiceHandle(hService);
        }

        CloseServiceHandle(hSCManager);
    }

    return lpServiceConfig;
}