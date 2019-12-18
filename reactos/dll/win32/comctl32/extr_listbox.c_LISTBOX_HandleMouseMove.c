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
struct TYPE_5__ {int style; scalar_t__ item_height; scalar_t__ page_size; scalar_t__ width; scalar_t__ height; scalar_t__ focus_item; int /*<<< orphan*/  self; int /*<<< orphan*/  captured; } ;
typedef  scalar_t__ TIMER_DIRECTION ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  KillSystemTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LBS_MULTICOLUMN ; 
 int /*<<< orphan*/  LB_SCROLL_TIMEOUT ; 
 scalar_t__ LB_TIMER_DOWN ; 
 int /*<<< orphan*/  LB_TIMER_ID ; 
 scalar_t__ LB_TIMER_LEFT ; 
 scalar_t__ LB_TIMER_NONE ; 
 scalar_t__ LB_TIMER_RIGHT ; 
 scalar_t__ LB_TIMER_UP ; 
 scalar_t__ LISTBOX_GetItemFromPoint (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LISTBOX_HandleTimer (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ LISTBOX_Timer ; 
 int /*<<< orphan*/  SetSystemTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LISTBOX_HandleMouseMove( LB_DESCR *descr,
                                     INT x, INT y )
{
    INT index;
    TIMER_DIRECTION dir = LB_TIMER_NONE;

    if (!descr->captured) return;

    if (descr->style & LBS_MULTICOLUMN)
    {
        if (y < 0) y = 0;
        else if (y >= descr->item_height * descr->page_size)
            y = descr->item_height * descr->page_size - 1;

        if (x < 0)
        {
            dir = LB_TIMER_LEFT;
            x = 0;
        }
        else if (x >= descr->width)
        {
            dir = LB_TIMER_RIGHT;
            x = descr->width - 1;
        }
    }
    else
    {
        if (y < 0) dir = LB_TIMER_UP;  /* above */
        else if (y >= descr->height) dir = LB_TIMER_DOWN;  /* below */
    }

    index = LISTBOX_GetItemFromPoint( descr, x, y );
    if (index == -1) index = descr->focus_item;
    if (!LISTBOX_HandleTimer( descr, index, dir )) dir = LB_TIMER_NONE;

    /* Start/stop the system timer */

    if (dir != LB_TIMER_NONE)
        SetSystemTimer( descr->self, LB_TIMER_ID, LB_SCROLL_TIMEOUT, NULL);
    else if (LISTBOX_Timer != LB_TIMER_NONE)
        KillSystemTimer( descr->self, LB_TIMER_ID );
    LISTBOX_Timer = dir;
}