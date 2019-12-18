#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* root; } ;
struct TYPE_6__ {int state; struct TYPE_6__* lastChild; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;

/* Variables and functions */
 int TVIS_EXPANDED ; 

__attribute__((used)) static TREEVIEW_ITEM *
TREEVIEW_GetLastListItem(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *item)
{
    if (!item) return NULL;

    while (item->lastChild)
    {
       if (item->state & TVIS_EXPANDED)
          item = item->lastChild;
       else
          break;
    }

    if (item == infoPtr->root)
        return NULL;

    return item;
}