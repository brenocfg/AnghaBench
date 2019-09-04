#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_14__ {scalar_t__ lpBinaryPathName; } ;
struct TYPE_13__ {TYPE_2__* Info; TYPE_1__* pService; } ;
struct TYPE_12__ {scalar_t__ bIsUserAnAdmin; } ;
struct TYPE_11__ {scalar_t__ lpServiceName; scalar_t__ lpDisplayName; } ;
typedef  TYPE_3__* PSERVICEPROPSHEET ;
typedef  TYPE_4__* LPWSTR ;
typedef  TYPE_4__* LPQUERY_SERVICE_CONFIG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* GetServiceConfig (scalar_t__) ; 
 TYPE_4__* GetServiceDescription (scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IDC_DESCRIPTION ; 
 int /*<<< orphan*/  IDC_DISP_NAME ; 
 int /*<<< orphan*/  IDC_EDIT ; 
 int /*<<< orphan*/  IDC_EXEPATH ; 
 int /*<<< orphan*/  IDC_SERV_NAME ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetServiceStatusText (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetStartupType (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 

__attribute__((used)) static VOID
InitGeneralPage(PSERVICEPROPSHEET dlgInfo,
                HWND hwndDlg)
{
    LPQUERY_SERVICE_CONFIG pServiceConfig;
    LPWSTR lpDescription;

    /* set the service name */
    SendDlgItemMessageW(hwndDlg,
                        IDC_SERV_NAME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)dlgInfo->pService->lpServiceName);

    /* set the display name */
    SendDlgItemMessageW(hwndDlg,
                        IDC_DISP_NAME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)dlgInfo->pService->lpDisplayName);

    /* set the description */
    if ((lpDescription = GetServiceDescription(dlgInfo->pService->lpServiceName)))
    {
        SendDlgItemMessageW(hwndDlg,
                            IDC_DESCRIPTION,
                            WM_SETTEXT,
                            0,
                            (LPARAM)lpDescription);

        HeapFree(ProcessHeap,
                 0,
                 lpDescription);
    }

    pServiceConfig = GetServiceConfig(dlgInfo->pService->lpServiceName);
    if (pServiceConfig)
    {
        SendDlgItemMessageW(hwndDlg,
                            IDC_EXEPATH,
                            WM_SETTEXT,
                            0,
                            (LPARAM)pServiceConfig->lpBinaryPathName);
        HeapFree(ProcessHeap,
                 0,
                 pServiceConfig);
    }


    /* set startup type */
    SetStartupType(dlgInfo->pService->lpServiceName, hwndDlg);

    SetServiceStatusText(dlgInfo,
                         hwndDlg);

    if (dlgInfo->Info->bIsUserAnAdmin)
    {
        EnableWindow(GetDlgItem(hwndDlg, IDC_EDIT), TRUE);
    }
}