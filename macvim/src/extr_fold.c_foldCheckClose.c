#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_5__ {scalar_t__ w_p_fdl; TYPE_1__ w_cursor; int /*<<< orphan*/  w_folds; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  changed_window_setting () ; 
 scalar_t__ checkCloseRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  checkupdate (TYPE_2__*) ; 
 TYPE_2__* curwin ; 
 scalar_t__* p_fcl ; 

void
foldCheckClose()
{
    if (*p_fcl != NUL)	/* can only be "all" right now */
    {
	checkupdate(curwin);
	if (checkCloseRec(&curwin->w_folds, curwin->w_cursor.lnum,
							(int)curwin->w_p_fdl))
	    changed_window_setting();
    }
}