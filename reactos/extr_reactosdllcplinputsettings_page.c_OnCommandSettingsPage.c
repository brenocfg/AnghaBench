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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ lParam; void* iItem; void* mask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ LVITEM ;
typedef  int /*<<< orphan*/  INPUT_LIST_NODE ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  AddDialogProc ; 
 int /*<<< orphan*/  DialogBoxParamW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DialogBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EditDialogProc ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ *) ; 
#define  IDC_ADD_BUTTON 132 
 int /*<<< orphan*/  IDC_KEYLAYOUT_LIST ; 
#define  IDC_KEY_SET_BTN 131 
#define  IDC_PROP_BUTTON 130 
#define  IDC_REMOVE_BUTTON 129 
#define  IDC_SET_DEFAULT 128 
 int /*<<< orphan*/  IDD_ADD ; 
 int /*<<< orphan*/  IDD_INPUT_LANG_PROP ; 
 int /*<<< orphan*/  IDD_KEYSETTINGS ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  InputList_Remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InputList_SetDefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeySettingsDialogProc ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 void* LVIF_PARAM ; 
 int /*<<< orphan*/  LVNI_SELECTED ; 
 int /*<<< orphan*/  ListView_GetItem (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* ListView_GetNextItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateInputListView (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hApplet ; 

VOID
OnCommandSettingsPage(HWND hwndDlg, WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
        case IDC_ADD_BUTTON:
        {
            if (DialogBoxW(hApplet,
                           MAKEINTRESOURCEW(IDD_ADD),
                           hwndDlg,
                           AddDialogProc) == IDOK)
            {
                UpdateInputListView(GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST));
                PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
            }
        }
        break;

        case IDC_REMOVE_BUTTON:
        {
            HWND hwndList;
            
            hwndList = GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST);

            if (hwndList != NULL)
            {
                LVITEM item = { 0 };

                item.mask = LVIF_PARAM;
                item.iItem = ListView_GetNextItem(hwndList, -1, LVNI_SELECTED);

                if (ListView_GetItem(hwndList, &item) != FALSE)
                {
                    InputList_Remove((INPUT_LIST_NODE*) item.lParam);
                    UpdateInputListView(hwndList);
                    PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
                }
            }
        }
        break;

        case IDC_PROP_BUTTON:
        {
            HWND hwndList;
            
            hwndList = GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST);

            if (hwndList != NULL)
            {
                LVITEM item = { 0 };

                item.mask = LVIF_PARAM;
                item.iItem = ListView_GetNextItem(hwndList, -1, LVNI_SELECTED);

                if (ListView_GetItem(hwndList, &item) != FALSE)
                {
                    if (DialogBoxParamW(hApplet,
                                        MAKEINTRESOURCEW(IDD_INPUT_LANG_PROP),
                                        hwndDlg,
                                        EditDialogProc,
                                        item.lParam) == IDOK)
                    {
                        UpdateInputListView(hwndList);
                        PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
                    }
                }
            }
        }
        break;

        case IDC_SET_DEFAULT:
        {
            HWND hwndList;
            
            hwndList = GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST);

            if (hwndList != NULL)
            {
                LVITEM item = { 0 };

                item.mask = LVIF_PARAM;
                item.iItem = ListView_GetNextItem(hwndList, -1, LVNI_SELECTED);

                if (ListView_GetItem(hwndList, &item) != FALSE)
                {
                    InputList_SetDefault((INPUT_LIST_NODE*) item.lParam);
                    UpdateInputListView(hwndList);
                    PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
                }
            }
        }
        break;

        case IDC_KEY_SET_BTN:
        {
            DialogBoxW(hApplet,
                       MAKEINTRESOURCEW(IDD_KEYSETTINGS),
                       hwndDlg,
                       KeySettingsDialogProc);
        }
        break;
    }
}