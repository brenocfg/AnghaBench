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
struct TYPE_4__ {size_t iItem; int iSubItem; int /*<<< orphan*/ * pszText; scalar_t__ lParam; scalar_t__ iImage; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ LV_ITEM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LVIF_TEXT ; 
 int /*<<< orphan*/  LVM_SETITEMTEXT ; 
 void** ListItems_Cmds ; 
 int* ListItems_Locations ; 
 void** ListItems_Params ; 
 size_t ListView_GetItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListView_InsertItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hToolsListCtrl ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void AddItem ( DWORD name_id, DWORD descr_id, DWORD cmd_id , DWORD param_id, int csidl ) {
    TCHAR szTemp[256];
    LV_ITEM item;

    LoadString(hInst, name_id, szTemp, 256);
    memset(&item, 0, sizeof(LV_ITEM));
    item.mask = LVIF_TEXT;
    item.iImage = 0;
    item.pszText = szTemp;
    item.iItem = ListView_GetItemCount(hToolsListCtrl);
    item.lParam = 0;
    (void)ListView_InsertItem(hToolsListCtrl, &item);

    ListItems_Cmds[item.iItem] = cmd_id;
    ListItems_Params[item.iItem] = param_id;
    ListItems_Locations[item.iItem] = csidl;

    LoadString(hInst, descr_id, szTemp, 256);
    item.pszText = szTemp;
    item.iSubItem = 1;
    SendMessage(hToolsListCtrl, LVM_SETITEMTEXT, item.iItem, (LPARAM) &item);
}