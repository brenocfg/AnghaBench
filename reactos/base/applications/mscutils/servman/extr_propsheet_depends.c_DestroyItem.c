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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TreeView_GetChild (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TreeView_GetItemParam (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VOID
DestroyItem(HWND hTreeView,
            HTREEITEM hItem)
{
    HTREEITEM hChildItem;
    LPWSTR lpServiceName;

    /* Does this item have any children */
    hChildItem = TreeView_GetChild(hTreeView, hItem);
    if (hChildItem)
    {
        /* It does, recurse to that one */
        DestroyItem(hTreeView, hChildItem);
    }

    /* Get the string and free it */
    lpServiceName = (LPWSTR)TreeView_GetItemParam(hTreeView, hItem);
    if (lpServiceName)
    {
        HeapFree(GetProcessHeap(),
                 0,
                 lpServiceName);
    }
}