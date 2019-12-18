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
 int /*<<< orphan*/ * TreeView_GetNextSibling (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HTREEITEM TreeView_GetLastFromItem(HWND hTree, HTREEITEM hItem)
{
    HTREEITEM htiRet = NULL;
    HTREEITEM htiIterator;

    for (htiIterator = hItem ; htiIterator ; htiIterator = TreeView_GetNextSibling(hTree, htiIterator))
        htiRet = htiIterator;

    return htiRet;
}