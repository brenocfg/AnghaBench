#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  w_p_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_cursor () ; 
 TYPE_1__* curwin ; 
 int /*<<< orphan*/  update_curswant () ; 
 int /*<<< orphan*/  update_topline () ; 
 int /*<<< orphan*/  validate_cursor () ; 

void
update_topline_cursor()
{
    check_cursor();		/* put cursor on valid line */
    update_topline();
    if (!curwin->w_p_wrap)
	validate_cursor();
    update_curswant();
}