#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int wFlags; TYPE_2__* pLayout; TYPE_1__* pLocale; int /*<<< orphan*/  pszIndicator; } ;
struct TYPE_10__ {int mask; int iImage; scalar_t__ lParam; scalar_t__ iItem; int /*<<< orphan*/  pszText; } ;
struct TYPE_9__ {int /*<<< orphan*/  pszName; } ;
struct TYPE_8__ {int /*<<< orphan*/  pszName; } ;
typedef  TYPE_3__ LV_ITEM ;
typedef  scalar_t__ LPARAM ;
typedef  int INT ;
typedef  TYPE_4__ INPUT_LIST_NODE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateLayoutIcon (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int INPUT_LIST_NODE_FLAG_DEFAULT ; 
 int ImageList_AddIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int LVIF_IMAGE ; 
 int LVIF_PARAM ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/ * ListView_GetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ListView_GetItemCount (int /*<<< orphan*/ ) ; 
 int ListView_InsertItem (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ListView_SetItemText (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

__attribute__((used)) static VOID
AddToInputListView(HWND hwndList, INPUT_LIST_NODE *pInputNode)
{
    INT ItemIndex = -1;
    INT ImageIndex = -1;
    LV_ITEM item;
    HIMAGELIST hImageList;

    hImageList = ListView_GetImageList(hwndList, LVSIL_SMALL);

    if (hImageList != NULL)
    {
        HICON hLayoutIcon;

        hLayoutIcon = CreateLayoutIcon(pInputNode->pszIndicator,
                                       (pInputNode->wFlags & INPUT_LIST_NODE_FLAG_DEFAULT));

        if (hLayoutIcon != NULL)
        {
            ImageIndex = ImageList_AddIcon(hImageList, hLayoutIcon);
            DestroyIcon(hLayoutIcon);
        }
    }

    ZeroMemory(&item, sizeof(item));

    item.mask    = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
    item.pszText = pInputNode->pLocale->pszName;
    item.iItem   = ListView_GetItemCount(hwndList) + 1;
    item.lParam  = (LPARAM)pInputNode;
    item.iImage  = ImageIndex;

    ItemIndex = ListView_InsertItem(hwndList, &item);

    ListView_SetItemText(hwndList, ItemIndex, 1, pInputNode->pLayout->pszName);
}