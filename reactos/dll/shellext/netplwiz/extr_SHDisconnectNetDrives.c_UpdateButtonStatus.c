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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {scalar_t__ hwndFrom; int code; } ;
typedef  TYPE_1__* LPNMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CONNECTEDDRIVELIST ; 
 int /*<<< orphan*/  ID_OK ; 
#define  LVN_ITEMCHANGED 128 
 int /*<<< orphan*/  ListView_GetSelectedCount (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

VOID UpdateButtonStatus(WPARAM wParam, LPARAM lParam, HWND hDlg)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    HWND hListView = GetDlgItem(hDlg, IDC_CONNECTEDDRIVELIST);
    HWND hOkButton = GetDlgItem(hDlg, ID_OK);

    if (pnmh->hwndFrom == hListView)
    {
        switch (pnmh->code)
        {
            case LVN_ITEMCHANGED:
                if (ListView_GetSelectedCount(hListView))
                {
                    EnableWindow(hOkButton, TRUE);
                }
                else
                {
                    EnableWindow(hOkButton, FALSE);
                }
                break;
        }
    }
}