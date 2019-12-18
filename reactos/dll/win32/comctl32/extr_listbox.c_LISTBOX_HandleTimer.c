#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ top_item; scalar_t__ page_size; scalar_t__ focus_item; scalar_t__ nb_items; } ;
typedef  int TIMER_DIRECTION ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  LB_TIMER_DOWN 132 
#define  LB_TIMER_LEFT 131 
#define  LB_TIMER_NONE 130 
#define  LB_TIMER_RIGHT 129 
#define  LB_TIMER_UP 128 
 scalar_t__ LISTBOX_GetCurrentPageSize (TYPE_1__*) ; 
 int /*<<< orphan*/  LISTBOX_MoveCaret (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_HandleTimer( LB_DESCR *descr, INT index, TIMER_DIRECTION dir )
{
    switch(dir)
    {
    case LB_TIMER_UP:
        if (descr->top_item) index = descr->top_item - 1;
        else index = 0;
        break;
    case LB_TIMER_LEFT:
        if (descr->top_item) index -= descr->page_size;
        break;
    case LB_TIMER_DOWN:
        index = descr->top_item + LISTBOX_GetCurrentPageSize( descr );
        if (index == descr->focus_item) index++;
        if (index >= descr->nb_items) index = descr->nb_items - 1;
        break;
    case LB_TIMER_RIGHT:
        if (index + descr->page_size < descr->nb_items)
            index += descr->page_size;
        break;
    case LB_TIMER_NONE:
        break;
    }
    if (index == descr->focus_item) return FALSE;
    LISTBOX_MoveCaret( descr, index, FALSE );
    return TRUE;
}