#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {scalar_t__ ServiceList; scalar_t__ DisplayName; } ;
typedef  TYPE_1__* PSTOP_DATA ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddServiceNamesToStop (scalar_t__,scalar_t__) ; 
 scalar_t__ AllocAndLoadString (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 int /*<<< orphan*/  IDC_STOP_DEPENDS ; 
 int /*<<< orphan*/  IDC_STOP_DEPENDS_LB ; 
 int /*<<< orphan*/  IDI_SM_ICON ; 
 int /*<<< orphan*/  IDS_STOP_DEPENDS ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SendDlgItemMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETICON ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  _snwprintf (scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hInstance ; 
 int wcslen (scalar_t__) ; 

__attribute__((used)) static BOOL
InitDialog(HWND hDlg,
           UINT Message,
           WPARAM wParam,
           LPARAM lParam)
{
    PSTOP_DATA StopData;
    HWND hServiceListBox;
    LPWSTR lpPartialStr, lpStr;
    DWORD fullLen;
    HICON hIcon = NULL;
    BOOL bRet = FALSE;

    StopData = (PSTOP_DATA)lParam;


    /* Load the icon for the window */
    hIcon = (HICON)LoadImageW(hInstance,
                                MAKEINTRESOURCE(IDI_SM_ICON),
                                IMAGE_ICON,
                                GetSystemMetrics(SM_CXSMICON),
                                GetSystemMetrics(SM_CXSMICON),
                                0);
    if (hIcon)
    {
        /* Set it */
        SendMessageW(hDlg,
                        WM_SETICON,
                        ICON_SMALL,
                        (LPARAM)hIcon);
        DestroyIcon(hIcon);
    }

    /* Load the stop depends note */
    if (AllocAndLoadString(&lpPartialStr,
                            hInstance,
                            IDS_STOP_DEPENDS))
    {
        /* Get the length required */
        fullLen = wcslen(lpPartialStr) + wcslen(StopData->DisplayName) + 1;

        lpStr = HeapAlloc(ProcessHeap,
                          0,
                          fullLen * sizeof(WCHAR));
        if (lpStr)
        {
            /* Add the service name to the depends note */
            _snwprintf(lpStr,
                        fullLen,
                        lpPartialStr,
                        StopData->DisplayName);

            /* Add the string to the dialog */
            SendDlgItemMessageW(hDlg,
                                IDC_STOP_DEPENDS,
                                WM_SETTEXT,
                                0,
                                (LPARAM)lpStr);

            HeapFree(ProcessHeap,
                        0,
                        lpStr);

            bRet = TRUE;
        }

        LocalFree(lpPartialStr);
    }

    /* Display the list of services which need stopping */
    hServiceListBox = GetDlgItem(hDlg, IDC_STOP_DEPENDS_LB);
    if (hServiceListBox)
    {
        AddServiceNamesToStop(hServiceListBox,
                              (LPWSTR)StopData->ServiceList);
    }
 
    return bRet;
}