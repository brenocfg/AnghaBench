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
struct TYPE_3__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  hItem; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTREEITEM ;

/* Variables and functions */
 int TVIF_HANDLE ; 
 int TVIF_PARAM ; 
 scalar_t__ TreeView_GetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static LPARAM
TreeView_GetItemParam(HWND hTreeView,
                      HTREEITEM hItem)
{
    LPARAM lParam = 0;
    TVITEMW tv = {0};

    tv.mask = TVIF_PARAM | TVIF_HANDLE;
    tv.hItem = hItem;

    if (TreeView_GetItem(hTreeView, &tv))
    {
        lParam = tv.lParam;
    }

    return lParam;
}