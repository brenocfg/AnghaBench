#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tvis ;
struct TYPE_5__ {void* hItem; scalar_t__ pszText; int /*<<< orphan*/  mask; } ;
struct TYPE_6__ {TYPE_1__ itemex; void* hInsertAfter; void* hParent; } ;
typedef  TYPE_2__ TVINSERTSTRUCTW ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  SecureZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TVIF_TEXT ; 
 void* TreeView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 

HTREEITEM
InsertItem(HWND hTree,
           LPCWSTR szName,
           HTREEITEM hParent,
           HTREEITEM hInsertAfter)
{
    TVINSERTSTRUCTW tvis;
    SecureZeroMemory(&tvis, sizeof(tvis));

    tvis.hParent        = hParent;
    tvis.hInsertAfter   = hInsertAfter;
    tvis.itemex.mask    = TVIF_TEXT;
    tvis.itemex.pszText = (LPWSTR)szName;

    return (tvis.itemex.hItem = TreeView_InsertItem(hTree, &tvis));
}