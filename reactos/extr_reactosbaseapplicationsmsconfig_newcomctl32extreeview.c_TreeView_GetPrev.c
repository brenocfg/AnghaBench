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
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/ * TreeView_GetChild (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetLastFromItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetPrevSibling (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HTREEITEM TreeView_GetPrev(HWND hTree, HTREEITEM hItem)
{
    HTREEITEM hPrev, hTmp;

    if (!hTree)
        return NULL;

    hPrev = TreeView_GetPrevSibling(hTree, hItem);
    if (!hPrev)
        return TreeView_GetParent(hTree, hItem);

    hTmp = TreeView_GetChild(hTree, hPrev);
    if (hTmp)
        return TreeView_GetLastFromItem(hTree, hTmp);
    else
        return hPrev;
}