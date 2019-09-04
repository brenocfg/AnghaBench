#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  column ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int dwAttributes; } ;
struct TYPE_5__ {int mask; int iSubItem; char* pszText; int cx; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ LV_COLUMN ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  BST_UNCHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_KEY_LISTVIEW ; 
 int /*<<< orphan*/  IDC_PRESS_CL_KEY_RB ; 
 int /*<<< orphan*/  IDC_PRESS_SHIFT_KEY_RB ; 
 int KLF_SHIFTLOCK ; 
 int /*<<< orphan*/  LVCFMT_LEFT ; 
 int /*<<< orphan*/  LVCFMT_RIGHT ; 
 int LVCF_FMT ; 
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int /*<<< orphan*/  LVS_EX_FULLROWSELECT ; 
 int /*<<< orphan*/  ListView_InsertColumn (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ListView_SetExtendedListViewStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadKeysSettings () ; 
 int /*<<< orphan*/  UpdateKeySettingsListView (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 TYPE_2__ _KeySettings ; 

__attribute__((used)) static VOID
OnInitKeySettingsDialog(HWND hwndDlg)
{
    LV_COLUMN column;
    HWND hwndList;

    ReadKeysSettings();

    if (_KeySettings.dwAttributes & KLF_SHIFTLOCK)
    {
        CheckDlgButton(hwndDlg, IDC_PRESS_SHIFT_KEY_RB, BST_CHECKED);
        CheckDlgButton(hwndDlg, IDC_PRESS_CL_KEY_RB, BST_UNCHECKED);
    }
    else
    {
        CheckDlgButton(hwndDlg, IDC_PRESS_SHIFT_KEY_RB, BST_UNCHECKED);
        CheckDlgButton(hwndDlg, IDC_PRESS_CL_KEY_RB, BST_CHECKED);
    }

    hwndList = GetDlgItem(hwndDlg, IDC_KEY_LISTVIEW);

    ListView_SetExtendedListViewStyle(hwndList, LVS_EX_FULLROWSELECT);

    ZeroMemory(&column, sizeof(column));

    column.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    column.fmt      = LVCFMT_LEFT;
    column.iSubItem = 0;
    column.pszText  = L"";
    column.cx       = 210;
    ListView_InsertColumn(hwndList, 0, &column);

    column.fmt      = LVCFMT_RIGHT;
    column.cx       = 145;
    column.iSubItem = 1;
    column.pszText  = L"";
    ListView_InsertColumn(hwndList, 1, &column);

    UpdateKeySettingsListView(hwndList);
}