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
typedef  scalar_t__ linenr_T ;
struct TYPE_3__ {scalar_t__ lnum; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  changed_cline_bef_curs () ; 
 int /*<<< orphan*/  check_cursor () ; 
 int /*<<< orphan*/  check_cursor_col () ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  invalidate_botline () ; 

__attribute__((used)) static void
py_fix_cursor(linenr_T lo, linenr_T hi, linenr_T extra)
{
    if (curwin->w_cursor.lnum >= lo)
    {
	/* Adjust the cursor position if it's in/after the changed
	 * lines. */
	if (curwin->w_cursor.lnum >= hi)
	{
	    curwin->w_cursor.lnum += extra;
	    check_cursor_col();
	}
	else if (extra < 0)
	{
	    curwin->w_cursor.lnum = lo;
	    check_cursor();
	}
	else
	    check_cursor_col();
	changed_cline_bef_curs();
    }
    invalidate_botline();
}