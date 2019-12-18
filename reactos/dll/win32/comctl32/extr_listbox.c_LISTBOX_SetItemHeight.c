#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int style; size_t nb_items; size_t item_height; int /*<<< orphan*/  self; TYPE_1__* items; } ;
struct TYPE_7__ {size_t height; } ;
typedef  int LRESULT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_INDEX ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int LB_ERR ; 
 int LB_OKAY ; 
 int /*<<< orphan*/  LISTBOX_InvalidateItems (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  LISTBOX_UpdatePage (TYPE_2__*) ; 
 int /*<<< orphan*/  LISTBOX_UpdateScroll (TYPE_2__*) ; 
 size_t MAXBYTE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_SetItemHeight( LB_DESCR *descr, INT index, INT height, BOOL repaint )
{
    if (height > MAXBYTE)
        return -1;

    if (!height) height = 1;

    if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        if ((index < 0) || (index >= descr->nb_items))
        {
            SetLastError(ERROR_INVALID_INDEX);
            return LB_ERR;
        }
        TRACE("[%p]: item %d height = %d\n", descr->self, index, height );
        descr->items[index].height = height;
        LISTBOX_UpdateScroll( descr );
	if (repaint)
	    LISTBOX_InvalidateItems( descr, index );
    }
    else if (height != descr->item_height)
    {
        TRACE("[%p]: new height = %d\n", descr->self, height );
        descr->item_height = height;
        LISTBOX_UpdatePage( descr );
        LISTBOX_UpdateScroll( descr );
	if (repaint)
	    InvalidateRect( descr->self, 0, TRUE );
    }
    return LB_OKAY;
}