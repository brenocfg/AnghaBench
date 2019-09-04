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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int wFlags; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ INPUT_LIST_NODE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddToInputListView (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int INPUT_LIST_NODE_FLAG_DELETED ; 
 int /*<<< orphan*/  ImageList_RemoveAll (int /*<<< orphan*/ *) ; 
 TYPE_1__* InputList_GetFirst () ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  ListView_DeleteAllItems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ListView_GetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
UpdateInputListView(HWND hwndList)
{
    INPUT_LIST_NODE *pCurrentInputNode;
    HIMAGELIST hImageList;

    hImageList = ListView_GetImageList(hwndList, LVSIL_SMALL);
    if (hImageList != NULL)
    {
        ImageList_RemoveAll(hImageList);
    }

    ListView_DeleteAllItems(hwndList);

    for (pCurrentInputNode = InputList_GetFirst();
         pCurrentInputNode != NULL;
         pCurrentInputNode = pCurrentInputNode->pNext)
    {
        if (!(pCurrentInputNode->wFlags & INPUT_LIST_NODE_FLAG_DELETED))
        {
            AddToInputListView(hwndList, pCurrentInputNode);
        }
    }
}