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
struct TYPE_3__ {int /*<<< orphan*/  lpDescription; } ;
typedef  TYPE_1__ SERVICE_DESCRIPTION ;
typedef  int /*<<< orphan*/  SC_LOCK ;
typedef  scalar_t__ SC_HANDLE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ChangeServiceConfig2W (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetError () ; 
 int /*<<< orphan*/  LockServiceDatabase (scalar_t__) ; 
 scalar_t__ OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenServiceW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_LOCK ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CONFIG ; 
 int /*<<< orphan*/  SERVICE_CONFIG_DESCRIPTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnlockServiceDatabase (int /*<<< orphan*/ ) ; 

BOOL
SetServiceDescription(LPWSTR lpServiceName,
                      LPWSTR lpDescription)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hSc;
    SC_LOCK scLock;
    SERVICE_DESCRIPTION ServiceDescription;
    BOOL bRet = FALSE;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_LOCK);
    if (hSCManager)
    {
        scLock = LockServiceDatabase(hSCManager);
        if (scLock)
        {
            hSc = OpenServiceW(hSCManager,
                               lpServiceName,
                               SERVICE_CHANGE_CONFIG);
            if (hSc)
            {
                ServiceDescription.lpDescription = lpDescription;

                if (ChangeServiceConfig2W(hSc,
                                          SERVICE_CONFIG_DESCRIPTION,
                                          &ServiceDescription))
                {
                    bRet = TRUE;
                }

                CloseServiceHandle(hSc);
            }

            UnlockServiceDatabase(scLock);
        }

        CloseServiceHandle(hSCManager);
    }

    if (!bRet)
        GetError();

    return bRet;
}