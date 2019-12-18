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
 int /*<<< orphan*/ * TreeView_GetNextSibling (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HTREEITEM TreeView_GetNext(HWND hTree, HTREEITEM hItem)
{
    HTREEITEM hNext;

    if (!hTree)
        return NULL;

    hNext = TreeView_GetChild(hTree, hItem);
    if (hNext)
        return hNext;

    hNext = TreeView_GetNextSibling(hTree, hItem);
    if (hNext)
        return hNext;
    else
        return TreeView_GetNextSibling(hTree, TreeView_GetParent(hTree, hItem));
}