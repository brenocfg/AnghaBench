#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mask; scalar_t__ lParam; scalar_t__ cChildren; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  pszText; int /*<<< orphan*/  cchTextMax; } ;
struct TYPE_5__ {void* hParent; void* hInsertAfter; TYPE_1__ item; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  TYPE_2__ TVINSERTSTRUCTW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HTREEITEM ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  Image_Closed ; 
 int /*<<< orphan*/  Image_Open ; 
 scalar_t__ RegQueryInfoKeyW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TVIF_CHILDREN ; 
 int TVIF_IMAGE ; 
 int TVIF_PARAM ; 
 int TVIF_SELECTEDIMAGE ; 
 int TVIF_TEXT ; 
 scalar_t__ TVI_FIRST ; 
 scalar_t__ TVI_LAST ; 
 void* TreeView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HTREEITEM AddEntryToTree(HWND hwndTV, HTREEITEM hParent, LPWSTR label, HKEY hKey, DWORD dwChildren)
{
    TVITEMW tvi;
    TVINSERTSTRUCTW tvins;

    if (hKey)
    {
        if (RegQueryInfoKeyW(hKey, 0, 0, 0, &dwChildren, 0, 0, 0, 0, 0, 0, 0) != ERROR_SUCCESS)
        {
            dwChildren = 0;
        }
    }

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN | TVIF_PARAM;
    tvi.pszText = label;
    tvi.cchTextMax = wcslen(tvi.pszText);
    tvi.iImage = Image_Closed;
    tvi.iSelectedImage = Image_Open;
    tvi.cChildren = dwChildren;
    tvi.lParam = (LPARAM)hKey;
    tvins.item = tvi;
    tvins.hInsertAfter = (HTREEITEM)(hKey ? TVI_LAST : TVI_FIRST);
    tvins.hParent = hParent;
    return TreeView_InsertItem(hwndTV, &tvins);
}