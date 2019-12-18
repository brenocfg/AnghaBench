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
struct TYPE_3__ {int w_height; int w_topfill; int /*<<< orphan*/  w_topline; } ;

/* Variables and functions */
 TYPE_1__* curwin ; 
 int diff_check_fill (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int plines_nofill (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
max_topfill()
{
    int		n;

    n = plines_nofill(curwin->w_topline);
    if (n >= curwin->w_height)
	curwin->w_topfill = 0;
    else
    {
	curwin->w_topfill = diff_check_fill(curwin, curwin->w_topline);
	if (curwin->w_topfill + n > curwin->w_height)
	    curwin->w_topfill = curwin->w_height - n;
    }
}