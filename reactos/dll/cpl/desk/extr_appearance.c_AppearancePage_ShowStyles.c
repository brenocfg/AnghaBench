#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_4__ {scalar_t__ DisplayName; struct TYPE_4__* NextStyle; } ;
typedef  TYPE_1__* PTHEME_STYLE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppearancePage_ShowStyles(HWND hwndDlg, int nIDDlgItem, PTHEME_STYLE pStyles, PTHEME_STYLE pActiveStyle)
{
    int iListIndex;
    HWND hwndList = GetDlgItem(hwndDlg, nIDDlgItem);
    PTHEME_STYLE pCurrentStyle;

    SendMessage(hwndList, CB_RESETCONTENT , 0, 0);

    for (pCurrentStyle = pStyles;
         pCurrentStyle;
         pCurrentStyle = pCurrentStyle->NextStyle)
    {
        iListIndex = SendMessage(hwndList, CB_ADDSTRING, 0, (LPARAM)pCurrentStyle->DisplayName);
        SendMessage(hwndList, CB_SETITEMDATA, iListIndex, (LPARAM)pCurrentStyle);
        if (pCurrentStyle == pActiveStyle)
        {
            SendMessage(hwndList, CB_SETCURSEL, (WPARAM)iListIndex, 0);
        }
    }
}