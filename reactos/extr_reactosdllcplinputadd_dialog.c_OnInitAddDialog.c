#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ dwId; int /*<<< orphan*/  pszName; struct TYPE_6__* pNext; } ;
typedef  TYPE_1__ LOCALE_LIST_NODE ;
typedef  TYPE_1__ LAYOUT_LIST_NODE ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ComboBox_AddString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetDefaultLayoutForLocale (scalar_t__) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemDefaultLCID () ; 
 int /*<<< orphan*/  IDC_INPUT_LANG_COMBO ; 
 int /*<<< orphan*/  IDC_KEYBOARD_LO_COMBO ; 
 TYPE_1__* LayoutList_GetFirst () ; 
 TYPE_1__* LocaleList_GetFirst () ; 

__attribute__((used)) static VOID
OnInitAddDialog(HWND hwndDlg)
{
    HWND hwndLocaleCombo = GetDlgItem(hwndDlg, IDC_INPUT_LANG_COMBO);
    HWND hwndLayoutCombo = GetDlgItem(hwndDlg, IDC_KEYBOARD_LO_COMBO);
    LOCALE_LIST_NODE *pCurrentLocale;
    LAYOUT_LIST_NODE *pCurrentLayout;
    DWORD dwDefaultLocaleId;
    DWORD dwDefaultLayoutId;
    INT iItemIndex;

    dwDefaultLocaleId = GetSystemDefaultLCID();

    for (pCurrentLocale = LocaleList_GetFirst();
         pCurrentLocale != NULL;
         pCurrentLocale = pCurrentLocale->pNext)
    {
        iItemIndex = ComboBox_AddString(hwndLocaleCombo, pCurrentLocale->pszName);
        ComboBox_SetItemData(hwndLocaleCombo, iItemIndex, pCurrentLocale);

        if (pCurrentLocale->dwId == dwDefaultLocaleId)
        {
            ComboBox_SetCurSel(hwndLocaleCombo, iItemIndex);
        }
    }

    dwDefaultLayoutId = GetDefaultLayoutForLocale(dwDefaultLocaleId);

    for (pCurrentLayout = LayoutList_GetFirst();
         pCurrentLayout != NULL;
         pCurrentLayout = pCurrentLayout->pNext)
    {
        iItemIndex = ComboBox_AddString(hwndLayoutCombo, pCurrentLayout->pszName);
        ComboBox_SetItemData(hwndLayoutCombo, iItemIndex, pCurrentLayout);

        if (pCurrentLayout->dwId == dwDefaultLayoutId)
        {
            ComboBox_SetCurSel(hwndLayoutCombo, iItemIndex);
        }
    }

    if (dwDefaultLayoutId == 0)
        ComboBox_SetCurSel(hwndLayoutCombo, 0);
}