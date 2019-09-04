#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HTREEITEM ;

/* Variables and functions */
 scalar_t__ TVI_LAST ; 
 int /*<<< orphan*/  TreeView_DeleteItem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TreeView_GetNextSibling (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TreeView_GetParent (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TreeView_SelectItem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Tree_Item_Copy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void TreeView_DownItem(HWND hTree, HTREEITEM htiItemToDown)
{
    HTREEITEM htiNextItem, htiNewItem;

    if (!hTree || !htiItemToDown)
        return;

    htiNextItem = TreeView_GetNextSibling(hTree, htiItemToDown);
    if (!htiNextItem)
        htiNextItem = TVI_LAST;

    htiNewItem = Tree_Item_Copy(hTree, htiItemToDown, TreeView_GetParent(hTree, htiItemToDown), htiNextItem);
    TreeView_DeleteItem(hTree, htiItemToDown); // Delete the item and ALL its children.
    TreeView_SelectItem(hTree, htiNewItem);

    return;
}