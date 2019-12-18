#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_13__ {int /*<<< orphan*/  lpServiceName; TYPE_2__* lpDisplayName; } ;
struct TYPE_12__ {TYPE_1__* dlgInfo; scalar_t__ bDescriptionChanged; scalar_t__ bStartTypeChanged; scalar_t__ bDisplayNameChanged; scalar_t__ bBinaryPathChanged; } ;
struct TYPE_11__ {struct TYPE_11__* lpBinaryPathName; struct TYPE_11__* lpDisplayName; void* dwStartType; void* dwErrorControl; void* dwServiceType; } ;
struct TYPE_10__ {TYPE_9__* pService; int /*<<< orphan*/  Info; } ;
typedef  TYPE_2__* PWSTR ;
typedef  TYPE_3__* PPAGEDATA ;
typedef  TYPE_2__* LPQUERY_SERVICE_CONFIG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  ChangeListViewText (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDC_DESCRIPTION ; 
 int /*<<< orphan*/  IDC_DISP_NAME ; 
 int /*<<< orphan*/  IDC_EXEPATH ; 
 int /*<<< orphan*/  IDC_START_TYPE ; 
 int /*<<< orphan*/  LVDESC ; 
 int /*<<< orphan*/  LVNAME ; 
 int /*<<< orphan*/  LVSTARTUP ; 
 int /*<<< orphan*/  ProcessHeap ; 
 void* SERVICE_AUTO_START ; 
 void* SERVICE_DEMAND_START ; 
 void* SERVICE_DISABLED ; 
 void* SERVICE_NO_CHANGE ; 
 int SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SetServiceConfig (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetServiceDescription (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 

VOID
SaveDlgInfo(PPAGEDATA pPageData,
            HWND hwndDlg)
{
    LPQUERY_SERVICE_CONFIG pServiceConfig = NULL;
    PWSTR pDisplayName = NULL;
    PWSTR pDescription;
    INT nLength;
    DWORD StartUp;

    pServiceConfig = HeapAlloc(ProcessHeap,
                               HEAP_ZERO_MEMORY,
                               sizeof(*pServiceConfig));
    if (pServiceConfig)
    {
        pServiceConfig->dwServiceType = SERVICE_NO_CHANGE;
        pServiceConfig->dwErrorControl = SERVICE_NO_CHANGE;
        pServiceConfig->dwStartType = SERVICE_NO_CHANGE;

        if (pPageData->bStartTypeChanged)
        {
            StartUp = SendDlgItemMessageW(hwndDlg, IDC_START_TYPE, CB_GETCURSEL, 0, 0);
            switch (StartUp)
            {
                case 0:
                    pServiceConfig->dwStartType = SERVICE_AUTO_START;
                    break;

                case 1:
                    pServiceConfig->dwStartType = SERVICE_DEMAND_START;
                    break;
                case 2:
                    pServiceConfig->dwStartType = SERVICE_DISABLED;
                    break;
            }
        }

        if (pPageData->bBinaryPathChanged)
        {
            nLength = SendDlgItemMessageW(hwndDlg, IDC_EXEPATH, WM_GETTEXTLENGTH, 0, 0);
            pServiceConfig->lpBinaryPathName = HeapAlloc(ProcessHeap,
                                                         HEAP_ZERO_MEMORY,
                                                         (nLength + 1) * sizeof(WCHAR));
            if (pServiceConfig->lpBinaryPathName != NULL)
                SendDlgItemMessageW(hwndDlg, IDC_EXEPATH, WM_GETTEXT, nLength + 1, (LPARAM)pServiceConfig->lpBinaryPathName);
        }

        if (pPageData->bDisplayNameChanged)
        {
            nLength = SendDlgItemMessageW(hwndDlg, IDC_DISP_NAME, WM_GETTEXTLENGTH, 0, 0);
            pDisplayName = HeapAlloc(ProcessHeap,
                                     HEAP_ZERO_MEMORY,
                                     (nLength + 1) * sizeof(WCHAR));
            if (pDisplayName != NULL)
            {
                SendDlgItemMessageW(hwndDlg, IDC_DISP_NAME, WM_GETTEXT, nLength + 1, (LPARAM)pDisplayName);

                if (pPageData->dlgInfo->pService->lpDisplayName)
                    HeapFree(ProcessHeap, 0, pPageData->dlgInfo->pService->lpDisplayName);

                pPageData->dlgInfo->pService->lpDisplayName = pDisplayName;
                pServiceConfig->lpDisplayName = pDisplayName;
            }
        }

        if (SetServiceConfig(pServiceConfig,
                             pPageData->dlgInfo->pService->lpServiceName,
                             NULL))
        {
            if (pPageData->bDisplayNameChanged)
                ChangeListViewText(pPageData->dlgInfo->Info,
                                   pPageData->dlgInfo->pService,
                                   LVNAME);

            if (pPageData->bStartTypeChanged)
                ChangeListViewText(pPageData->dlgInfo->Info,
                                   pPageData->dlgInfo->pService,
                                   LVSTARTUP);
        }

        if (pServiceConfig->lpBinaryPathName != NULL)
            HeapFree(ProcessHeap, 0, pServiceConfig->lpBinaryPathName);

        HeapFree(ProcessHeap, 0, pServiceConfig);
    }

    if (pPageData->bDescriptionChanged)
    {
        nLength = SendDlgItemMessageW(hwndDlg, IDC_DESCRIPTION, WM_GETTEXTLENGTH, 0, 0);
        pDescription = HeapAlloc(ProcessHeap, HEAP_ZERO_MEMORY, (nLength + 1) * sizeof(WCHAR));
        if (pDescription != NULL)
        {
            SendDlgItemMessageW(hwndDlg, IDC_DESCRIPTION, WM_GETTEXT, nLength + 1, (LPARAM)pDescription);

            if (SetServiceDescription(pPageData->dlgInfo->pService->lpServiceName,
                                      pDescription))
            {
                ChangeListViewText(pPageData->dlgInfo->Info,
                                   pPageData->dlgInfo->pService,
                                   LVDESC);
            }

            HeapFree(ProcessHeap, 0, pDescription);
        }
    }
}