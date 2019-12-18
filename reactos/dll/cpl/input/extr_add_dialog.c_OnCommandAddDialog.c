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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  dwId; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwId; } ;
typedef  TYPE_1__ LOCALE_LIST_NODE ;
typedef  TYPE_2__ LAYOUT_LIST_NODE ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CBN_SELCHANGE ; 
 int /*<<< orphan*/  ComboBox_GetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 scalar_t__ ComboBox_GetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDefaultLayoutForLocale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
#define  IDCANCEL 130 
#define  IDC_INPUT_LANG_COMBO 129 
 int const IDC_KEYBOARD_LO_COMBO ; 
#define  IDOK 128 
 int /*<<< orphan*/  InputList_Add (TYPE_1__*,TYPE_2__*) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
OnCommandAddDialog(HWND hwndDlg, WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
        case IDOK:
        {
            HWND hwndLocaleCombo = GetDlgItem(hwndDlg, IDC_INPUT_LANG_COMBO);
            HWND hwndLayoutCombo = GetDlgItem(hwndDlg, IDC_KEYBOARD_LO_COMBO);
            LOCALE_LIST_NODE *pCurrentLocale;
            LAYOUT_LIST_NODE *pCurrentLayout;

            pCurrentLocale = (LOCALE_LIST_NODE*)ComboBox_GetItemData(hwndLocaleCombo,
                                                                     ComboBox_GetCurSel(hwndLocaleCombo));
            pCurrentLayout = (LAYOUT_LIST_NODE*)ComboBox_GetItemData(hwndLayoutCombo,
                                                                     ComboBox_GetCurSel(hwndLayoutCombo));

            InputList_Add(pCurrentLocale, pCurrentLayout);

            EndDialog(hwndDlg, LOWORD(wParam));
        }
        break;

        case IDCANCEL:
        {
            EndDialog(hwndDlg, LOWORD(wParam));
        }
        break;

        case IDC_INPUT_LANG_COMBO:
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                HWND hwndLocaleCombo = GetDlgItem(hwndDlg, IDC_INPUT_LANG_COMBO);
                HWND hwndLayoutCombo = GetDlgItem(hwndDlg, IDC_KEYBOARD_LO_COMBO);
                LOCALE_LIST_NODE *pCurrentLocale;

                pCurrentLocale = (LOCALE_LIST_NODE*)ComboBox_GetItemData(hwndLocaleCombo,
                                                                         ComboBox_GetCurSel(hwndLocaleCombo));
                if (pCurrentLocale != NULL)
                {
                    DWORD dwLayoutId;
                    INT iIndex;
                    INT iCount;

                    dwLayoutId = GetDefaultLayoutForLocale(pCurrentLocale->dwId);

                    iCount = ComboBox_GetCount(hwndLayoutCombo);

                    for (iIndex = 0; iIndex < iCount; iIndex++)
                    {
                        LAYOUT_LIST_NODE *pCurrentLayout;

                        pCurrentLayout = (LAYOUT_LIST_NODE*)ComboBox_GetItemData(hwndLayoutCombo, iIndex);

                        if (pCurrentLayout != NULL && pCurrentLayout->dwId == dwLayoutId)
                        {
                            ComboBox_SetCurSel(hwndLayoutCombo, iIndex);
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}