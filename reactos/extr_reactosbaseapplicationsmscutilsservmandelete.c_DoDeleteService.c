#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pCurrentService; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpServiceName; } ;
typedef  scalar_t__ SC_HANDLE ;
typedef  TYPE_2__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 int /*<<< orphan*/  DELETE ; 
 scalar_t__ DeleteService (scalar_t__) ; 
 int /*<<< orphan*/  DisplayString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDS_DELETE_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenServiceW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static BOOL
DoDeleteService(PMAIN_WND_INFO Info,
                HWND hDlg)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hSc;
    BOOL bRet = FALSE;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (hSCManager)
    {
        hSc = OpenServiceW(hSCManager,
                           Info->pCurrentService->lpServiceName,
                           DELETE);
        if (hSc)
        {
            if (DeleteService(hSc))
            {
                LPWSTR lpSuccess;

                /* report success to user */
                if (AllocAndLoadString(&lpSuccess,
                                       hInstance,
                                       IDS_DELETE_SUCCESS))
                {
                    DisplayString(lpSuccess);

                    LocalFree(lpSuccess);
                }

                bRet = TRUE;
            }

            CloseServiceHandle(hSc);
        }

        CloseServiceHandle(hSCManager);
    }

    return bRet;
}