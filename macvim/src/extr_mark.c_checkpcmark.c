#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lnum; } ;
struct TYPE_4__ {TYPE_1__ w_prev_pcmark; TYPE_1__ w_pcmark; int /*<<< orphan*/  w_cursor; } ;

/* Variables and functions */
 TYPE_2__* curwin ; 
 scalar_t__ equalpos (TYPE_1__,int /*<<< orphan*/ ) ; 

void
checkpcmark()
{
    if (curwin->w_prev_pcmark.lnum != 0
	    && (equalpos(curwin->w_pcmark, curwin->w_cursor)
		|| curwin->w_pcmark.lnum == 0))
    {
	curwin->w_pcmark = curwin->w_prev_pcmark;
	curwin->w_prev_pcmark.lnum = 0;		/* Show it has been checked */
    }
}