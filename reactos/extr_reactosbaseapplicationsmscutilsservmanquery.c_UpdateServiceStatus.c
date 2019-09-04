#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ServiceStatusProcess; int /*<<< orphan*/  lpServiceName; } ;
typedef  int /*<<< orphan*/  SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_1__ ENUM_SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryServiceStatusEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SC_STATUS_PROCESS_INFO ; 
 int /*<<< orphan*/  SERVICE_QUERY_STATUS ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
UpdateServiceStatus(ENUM_SERVICE_STATUS_PROCESS* pService)
{
    SC_HANDLE hScm;
    BOOL bRet = FALSE;

    hScm = OpenSCManagerW(NULL,
                          NULL,
                          SC_MANAGER_ENUMERATE_SERVICE);
    if (hScm != NULL)
    {
        SC_HANDLE hService;

        hService = OpenServiceW(hScm,
                                pService->lpServiceName,
                                SERVICE_QUERY_STATUS);
        if (hService)
        {
            DWORD size;

            QueryServiceStatusEx(hService,
                                 SC_STATUS_PROCESS_INFO,
                                 (LPBYTE)&pService->ServiceStatusProcess,
                                 sizeof(SERVICE_STATUS_PROCESS),
                                 &size);

            CloseServiceHandle(hService);
            bRet = TRUE;
        }

        CloseServiceHandle(hScm);
    }

    return bRet;
}