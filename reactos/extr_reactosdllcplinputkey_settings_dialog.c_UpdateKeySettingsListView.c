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
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int dwLanguage; } ;
struct TYPE_5__ {int mask; scalar_t__ iItem; int /*<<< orphan*/ * pszText; } ;
typedef  TYPE_1__ LV_ITEM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_CTRL_SHIFT ; 
 int /*<<< orphan*/  IDS_LEFT_ALT_SHIFT ; 
 int /*<<< orphan*/  IDS_NONE ; 
 int /*<<< orphan*/  IDS_SWITCH_BET_INLANG ; 
 int LVIF_PARAM ; 
 int LVIF_STATE ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  ListView_DeleteAllItems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListView_InsertItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ListView_SetItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STR_LEN ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 TYPE_2__ _KeySettings ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
UpdateKeySettingsListView(HWND hwndList)
{
    WCHAR szBuffer[MAX_STR_LEN];
    LV_ITEM item;
    INT iItemIndex;

    ListView_DeleteAllItems(hwndList);

    ZeroMemory(&item, sizeof(item));

    LoadStringW(hApplet, IDS_SWITCH_BET_INLANG, szBuffer, ARRAYSIZE(szBuffer));
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
    item.pszText = szBuffer;
    item.iItem = 0;

    iItemIndex = ListView_InsertItem(hwndList, &item);

    if (_KeySettings.dwLanguage == 1)
    {
        LoadStringW(hApplet, IDS_LEFT_ALT_SHIFT, szBuffer, ARRAYSIZE(szBuffer));
    }
    else if (_KeySettings.dwLanguage == 2)
    {
        LoadStringW(hApplet, IDS_CTRL_SHIFT, szBuffer, ARRAYSIZE(szBuffer));
    }
    else
    {
        LoadStringW(hApplet, IDS_NONE, szBuffer, ARRAYSIZE(szBuffer));
    }

    ListView_SetItemText(hwndList, iItemIndex, 1, szBuffer);
}