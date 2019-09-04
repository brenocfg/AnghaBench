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
struct TYPE_3__ {scalar_t__ col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int cls () ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  dec_cursor () ; 
 int /*<<< orphan*/  inc_cursor () ; 

__attribute__((used)) static void
back_in_line()
{
    int		sclass;		    /* starting class */

    sclass = cls();
    for (;;)
    {
	if (curwin->w_cursor.col == 0)	    /* stop at start of line */
	    break;
	dec_cursor();
	if (cls() != sclass)		    /* stop at start of word */
	{
	    inc_cursor();
	    break;
	}
    }
}