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
struct TYPE_4__ {scalar_t__ nb_items; int selected_item; int anchor_item; int /*<<< orphan*/ * items; scalar_t__ focus_item; scalar_t__ top_item; } ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTBOX_DeleteItem (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void LISTBOX_ResetContent( LB_DESCR *descr )
{
    INT i;

    for(i = descr->nb_items - 1; i>=0; i--) LISTBOX_DeleteItem( descr, i);
    HeapFree( GetProcessHeap(), 0, descr->items );
    descr->nb_items      = 0;
    descr->top_item      = 0;
    descr->selected_item = -1;
    descr->focus_item    = 0;
    descr->anchor_item   = -1;
    descr->items         = NULL;
}