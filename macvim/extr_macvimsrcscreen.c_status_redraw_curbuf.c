#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ w_status_height; scalar_t__ w_buffer; int /*<<< orphan*/  w_redr_status; struct TYPE_3__* w_next; } ;
typedef  TYPE_1__ win_T ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VALID ; 
 scalar_t__ curbuf ; 
 TYPE_1__* firstwin ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 

void
status_redraw_curbuf()
{
    win_T	*wp;

    for (wp = firstwin; wp; wp = wp->w_next)
	if (wp->w_status_height != 0 && wp->w_buffer == curbuf)
	{
	    wp->w_redr_status = TRUE;
	    redraw_later(VALID);
	}
}