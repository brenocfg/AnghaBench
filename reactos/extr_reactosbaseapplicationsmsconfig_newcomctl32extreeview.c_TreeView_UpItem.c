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
 scalar_t__ TVI_FIRST ; 
 int /*<<< orphan*/  TreeView_DeleteItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TreeView_GetParent (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TreeView_GetPrevSibling (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TreeView_SelectItem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Tree_Item_Copy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void TreeView_UpItem(HWND hTree, HTREEITEM htiItemToUp)
{
    HTREEITEM htiPrevItem, htiPrevPrevItem, htiNewItem;

    if (!hTree || !htiItemToUp)
        return;

    htiPrevItem     = TreeView_GetPrevSibling(hTree, htiItemToUp);
    htiPrevPrevItem = TreeView_GetPrevSibling(hTree, htiPrevItem);
    if (!htiPrevPrevItem)
        htiPrevPrevItem = TVI_FIRST;
    // if htiPrevItem == NULL , htiPrevPrevItem == NULL.

    htiNewItem = Tree_Item_Copy(hTree, htiItemToUp, TreeView_GetParent(hTree, htiItemToUp), htiPrevPrevItem);
    TreeView_DeleteItem(hTree, htiItemToUp); // Delete the item and ALL its children.
    TreeView_SelectItem(hTree, htiNewItem);

    return;
}