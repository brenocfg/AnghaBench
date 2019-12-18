#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; struct TYPE_4__* nextSibling; struct TYPE_4__* parent; struct TYPE_4__* firstChild; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;

/* Variables and functions */
 int TVIS_EXPANDED ; 

__attribute__((used)) static TREEVIEW_ITEM *
TREEVIEW_GetNextListItem(const TREEVIEW_INFO *infoPtr, const TREEVIEW_ITEM *tvItem)
{
    /*
     * If this item has children and is expanded, return the first child
     */
    if ((tvItem->state & TVIS_EXPANDED) && tvItem->firstChild != NULL)
    {
	return tvItem->firstChild;
    }


    /*
     * try to get the sibling
     */
    if (tvItem->nextSibling)
	return tvItem->nextSibling;

    /*
     * Otherwise, get the parent's sibling.
     */
    while (tvItem->parent)
    {
	tvItem = tvItem->parent;

	if (tvItem->nextSibling)
	    return tvItem->nextSibling;
    }

    return NULL;
}