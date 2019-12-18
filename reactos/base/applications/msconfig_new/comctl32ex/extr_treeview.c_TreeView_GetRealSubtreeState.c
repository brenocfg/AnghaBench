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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_GetCheckState (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetChild (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetNextSibling (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

UINT TreeView_GetRealSubtreeState(HWND hTree, HTREEITEM htiSubtreeItem)
{
#define OP(a, b) ((a) == (b) ? (a) : 2)

    HTREEITEM htiIterator       = TreeView_GetChild(hTree, htiSubtreeItem);
    UINT      uRealSubtreeState = TreeView_GetCheckState(hTree, htiIterator);
    /*
    while (htiIterator)
    {
        UINT temp = TreeView_GetCheckState(hTree, htiIterator);
        uRealSubtreeState = OP(uRealSubtreeState, temp);

        htiIterator = TreeView_GetNextSibling(hTree, htiIterator);
    }
    */
    while ( htiIterator && ( (htiIterator = TreeView_GetNextSibling(hTree, htiIterator)) != NULL ) )
    {
        UINT temp = TreeView_GetCheckState(hTree, htiIterator);
        uRealSubtreeState = OP(uRealSubtreeState, temp);
    }

    return uRealSubtreeState;
}