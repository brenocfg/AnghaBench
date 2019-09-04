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
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HTREEITEM ;
typedef  int /*<<< orphan*/ * HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ TreeView_GetSelection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_item_path (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,scalar_t__**,int*,int*) ; 
 scalar_t__* pathBuffer ; 

LPCWSTR GetItemPath(HWND hwndTV, HTREEITEM hItem, HKEY* phRootKey)
{
    int pathLen = 0, maxLen;

    *phRootKey = NULL;
    if (!pathBuffer) pathBuffer = HeapAlloc(GetProcessHeap(), 0, 1024);
    if (!pathBuffer) return NULL;
    *pathBuffer = 0;
    maxLen = (int) HeapSize(GetProcessHeap(), 0, pathBuffer);
    if (maxLen == -1) return NULL;
    if (!hItem) hItem = TreeView_GetSelection(hwndTV);
    if (!hItem) return NULL;
    if (!get_item_path(hwndTV, hItem, phRootKey, &pathBuffer, &pathLen, &maxLen))
    {
        return NULL;
    }
    return pathBuffer;
}