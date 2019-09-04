#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* pszText; int cchTextMax; void* hItem; int /*<<< orphan*/  mask; scalar_t__ lParam; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  int* LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HTREEITEM ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TVIF_PARAM ; 
 int /*<<< orphan*/  TVIF_TEXT ; 
 int /*<<< orphan*/  TreeView_GetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* TreeView_GetParent (int /*<<< orphan*/ ,void*) ; 
 size_t wcslen (int*) ; 

__attribute__((used)) static BOOL get_item_path(HWND hwndTV, HTREEITEM hItem, HKEY* phKey, LPWSTR* pKeyPath, int* pPathLen, int* pMaxLen)
{
    TVITEMW item;
    size_t maxLen, len;
    LPWSTR newStr;

    item.mask = TVIF_PARAM;
    item.hItem = hItem;
    if (!TreeView_GetItem(hwndTV, &item)) return FALSE;

    if (item.lParam)
    {
        /* found root key with valid key value */
        *phKey = (HKEY)item.lParam;
        return TRUE;
    }

    if(!get_item_path(hwndTV, TreeView_GetParent(hwndTV, hItem), phKey, pKeyPath, pPathLen, pMaxLen)) return FALSE;
    if (*pPathLen)
    {
        (*pKeyPath)[*pPathLen] = L'\\';
        ++(*pPathLen);
    }

    do
    {
        item.mask = TVIF_TEXT;
        item.hItem = hItem;
        item.pszText = *pKeyPath + *pPathLen;
        maxLen = *pMaxLen - *pPathLen;
        item.cchTextMax = (int) maxLen;
        if (!TreeView_GetItem(hwndTV, &item)) return FALSE;
        len = wcslen(item.pszText);
        if (len < maxLen - 1)
        {
            *pPathLen += (int) len;
            break;
        }
        newStr = HeapReAlloc(GetProcessHeap(), 0, *pKeyPath, *pMaxLen * 2);
        if (!newStr) return FALSE;
        *pKeyPath = newStr;
        *pMaxLen *= 2;
    }
    while(TRUE);

    return TRUE;
}