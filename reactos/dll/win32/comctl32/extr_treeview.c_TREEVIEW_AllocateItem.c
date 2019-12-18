#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_9__ {int /*<<< orphan*/  items; } ;
struct TYPE_8__ {TYPE_2__ const* infoPtr; scalar_t__ iExpandedImage; scalar_t__ iSelectedImage; scalar_t__ iImage; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;

/* Variables and functions */
 int DPA_InsertPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ I_IMAGENONE ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static TREEVIEW_ITEM *
TREEVIEW_AllocateItem(const TREEVIEW_INFO *infoPtr)
{
    TREEVIEW_ITEM *newItem = heap_alloc_zero(sizeof(*newItem));

    if (!newItem)
	return NULL;

    /* I_IMAGENONE would make more sense but this is neither what is
     * documented (MSDN doesn't specify) nor what Windows actually does
     * (it sets it to zero)... and I can so imagine an application using
     * inc/dec to toggle the images. */
    newItem->iImage = 0;
    newItem->iSelectedImage = 0;
    newItem->iExpandedImage = (WORD)I_IMAGENONE;
    newItem->infoPtr = infoPtr;

    if (DPA_InsertPtr(infoPtr->items, INT_MAX, newItem) == -1)
    {
        heap_free(newItem);
        return NULL;
    }

    return newItem;
}