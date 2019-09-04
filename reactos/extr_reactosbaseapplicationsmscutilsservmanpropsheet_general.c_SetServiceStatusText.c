#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {TYPE_2__* pService; } ;
struct TYPE_5__ {scalar_t__ dwCurrentState; } ;
struct TYPE_6__ {TYPE_1__ ServiceStatusProcess; } ;
typedef  TYPE_3__* PSERVICEPROPSHEET ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SERV_STATUS ; 
 int /*<<< orphan*/  IDS_SERVICES_STARTED ; 
 int /*<<< orphan*/  IDS_SERVICES_STOPPED ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ SERVICE_RUNNING ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
SetServiceStatusText(PSERVICEPROPSHEET dlgInfo,
                     HWND hwndDlg)
{
    LPWSTR lpStatus;
    UINT id;

    if (dlgInfo->pService->ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING)
    {
        id = IDS_SERVICES_STARTED;
    }
    else
    {
        id = IDS_SERVICES_STOPPED;
    }

    if (AllocAndLoadString(&lpStatus,
                           hInstance,
                           id))
    {
        SendDlgItemMessageW(hwndDlg,
                            IDC_SERV_STATUS,
                            WM_SETTEXT,
                            0,
                            (LPARAM)lpStatus);
        LocalFree(lpStatus);
    }
}