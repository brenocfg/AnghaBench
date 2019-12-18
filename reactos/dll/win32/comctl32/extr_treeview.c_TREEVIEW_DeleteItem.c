#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  bRedraw; TYPE_1__* root; TYPE_1__* dropItem; TYPE_1__* insertMarkItem; TYPE_1__* selectedItem; TYPE_1__* firstVisible; } ;
struct TYPE_31__ {struct TYPE_31__* firstChild; struct TYPE_31__* parent; struct TYPE_31__* prevSibling; struct TYPE_31__* nextSibling; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;
typedef  scalar_t__ LRESULT ;
typedef  TYPE_1__* HTREEITEM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISVISIBLE (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TREEVIEW_DoSelectItem (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TREEVIEW_GetPrevListItem (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_HasChildren (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_Invalidate (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ TREEVIEW_IsChildOf (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_ItemName (TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_RecalculateVisibleOrder (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_RemoveItem (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_RemoveTree (TYPE_2__*) ; 
 int /*<<< orphan*/  TREEVIEW_SetFirstVisible (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  TREEVIEW_UpdateScrollBars (TYPE_2__*) ; 
 scalar_t__ TREEVIEW_ValidItem (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_VerifyTree (TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TVC_UNKNOWN ; 
 int /*<<< orphan*/  TVGN_CARET ; 
 TYPE_1__* TVI_ROOT ; 

__attribute__((used)) static LRESULT
TREEVIEW_DeleteItem(TREEVIEW_INFO *infoPtr, HTREEITEM item)
{
    TREEVIEW_ITEM *newSelection = NULL;
    TREEVIEW_ITEM *newFirstVisible = NULL;
    TREEVIEW_ITEM *parent, *prev = NULL;
    BOOL visible = FALSE;

    if (item == TVI_ROOT || !item)
    {
	TRACE("TVI_ROOT\n");
	parent = infoPtr->root;
	newSelection = NULL;
	visible = TRUE;
	TREEVIEW_RemoveTree(infoPtr);
    }
    else
    {
	if (!TREEVIEW_ValidItem(infoPtr, item))
	    return FALSE;

	TRACE("%p (%s)\n", item, TREEVIEW_ItemName(item));
	parent = item->parent;

        if (ISVISIBLE(item))
        {
            prev = TREEVIEW_GetPrevListItem(infoPtr, item);
            visible = TRUE;
        }

	if (infoPtr->selectedItem != NULL
	    && (item == infoPtr->selectedItem
		|| TREEVIEW_IsChildOf(item, infoPtr->selectedItem)))
	{
	    if (item->nextSibling)
		newSelection = item->nextSibling;
	    else if (item->parent != infoPtr->root)
		newSelection = item->parent;
            else
                newSelection = item->prevSibling;
            TRACE("newSelection = %p\n", newSelection);
	}

	if (infoPtr->firstVisible == item)
	{
	    visible = TRUE;
	    if (item->nextSibling)
	       newFirstVisible = item->nextSibling;
	    else if (item->prevSibling)
	       newFirstVisible = item->prevSibling;
	    else if (item->parent != infoPtr->root)
	       newFirstVisible = item->parent;
	    TREEVIEW_SetFirstVisible(infoPtr, NULL, TRUE);
	}
	else
	    newFirstVisible = infoPtr->firstVisible;

	TREEVIEW_RemoveItem(infoPtr, item);
    }

    /* Don't change if somebody else already has (infoPtr->selectedItem is cleared by FreeItem). */
    if (!infoPtr->selectedItem && newSelection)
    {
	if (TREEVIEW_ValidItem(infoPtr, newSelection))
	    TREEVIEW_DoSelectItem(infoPtr, TVGN_CARET, newSelection, TVC_UNKNOWN);
    }

    /* Validate insertMark dropItem.
     * hotItem ??? - used for comparison only.
     */
    if (!TREEVIEW_ValidItem(infoPtr, infoPtr->insertMarkItem))
	infoPtr->insertMarkItem = 0;

    if (!TREEVIEW_ValidItem(infoPtr, infoPtr->dropItem))
	infoPtr->dropItem = 0;

    if (!TREEVIEW_ValidItem(infoPtr, newFirstVisible))
        newFirstVisible = infoPtr->root->firstChild;

    TREEVIEW_VerifyTree(infoPtr);

    if (visible)
        TREEVIEW_SetFirstVisible(infoPtr, newFirstVisible, TRUE);

    if (!infoPtr->bRedraw) return TRUE;

    if (visible)
    {
       TREEVIEW_RecalculateVisibleOrder(infoPtr, prev);
       TREEVIEW_UpdateScrollBars(infoPtr);
       TREEVIEW_Invalidate(infoPtr, NULL);
    }
    else if (ISVISIBLE(parent) && !TREEVIEW_HasChildren(infoPtr, parent))
    {
       /* parent lost '+/-' - update it */
       TREEVIEW_Invalidate(infoPtr, parent);
    }

    return TRUE;
}