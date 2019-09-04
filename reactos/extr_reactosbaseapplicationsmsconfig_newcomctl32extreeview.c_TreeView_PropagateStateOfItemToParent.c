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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  INDEXTOSTATEIMAGEMASK (scalar_t__) ; 
 int /*<<< orphan*/  TVIS_STATEIMAGEMASK ; 
 int /*<<< orphan*/  TreeView_GetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TreeView_GetRealSubtreeState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_SetItemState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void TreeView_PropagateStateOfItemToParent(HWND hTree, HTREEITEM htiItem)
{
    HTREEITEM htiParent;
    UINT uGlobalSiblingsCheckState;

    if (!hTree || !htiItem /* || htiItem == TVI_ROOT */)
        return;

    htiParent = TreeView_GetParent(hTree, htiItem);
    if (!htiParent)
        return;

    uGlobalSiblingsCheckState = TreeView_GetRealSubtreeState(hTree, htiParent);
    TreeView_SetItemState(hTree, htiParent, INDEXTOSTATEIMAGEMASK(uGlobalSiblingsCheckState + 1), TVIS_STATEIMAGEMASK);
    TreeView_PropagateStateOfItemToParent(hTree, htiParent);

    return;
}