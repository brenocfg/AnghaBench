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
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDC_WAIT ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RefreshTreeItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TreeView_GetChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TreeView_GetNextSibling (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TreeView_GetRoot (int /*<<< orphan*/ ) ; 
 scalar_t__ TreeView_GetSelection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_SelectItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

BOOL RefreshTreeView(HWND hwndTV)
{
    HTREEITEM hItem;
    HTREEITEM hSelectedItem;
    HCURSOR hcursorOld;

    hSelectedItem = TreeView_GetSelection(hwndTV);
    hcursorOld = SetCursor(LoadCursor(NULL, IDC_WAIT));
    SendMessageW(hwndTV, WM_SETREDRAW, FALSE, 0);

    hItem = TreeView_GetChild(hwndTV, TreeView_GetRoot(hwndTV));
    while (hItem)
    {
        RefreshTreeItem(hwndTV, hItem);
        hItem = TreeView_GetNextSibling(hwndTV, hItem);
    }

    SendMessageW(hwndTV, WM_SETREDRAW, TRUE, 0);
    SetCursor(hcursorOld);

    /* We reselect the currently selected node, this will prompt a refresh of the listview. */
    (void)TreeView_SelectItem(hwndTV, hSelectedItem);
    return TRUE;
}