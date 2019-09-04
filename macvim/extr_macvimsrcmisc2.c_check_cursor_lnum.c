#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ml_line_count; } ;
struct TYPE_8__ {TYPE_1__ b_ml; } ;
struct TYPE_6__ {int lnum; } ;
struct TYPE_7__ {TYPE_2__ w_cursor; } ;

/* Variables and functions */
 TYPE_4__* curbuf ; 
 TYPE_3__* curwin ; 

void
check_cursor_lnum()
{
    if (curwin->w_cursor.lnum > curbuf->b_ml.ml_line_count)
    {
#ifdef FEAT_FOLDING
	/* If there is a closed fold at the end of the file, put the cursor in
	 * its first line.  Otherwise in the last line. */
	if (!hasFolding(curbuf->b_ml.ml_line_count,
						&curwin->w_cursor.lnum, NULL))
#endif
	    curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
    }
    if (curwin->w_cursor.lnum <= 0)
	curwin->w_cursor.lnum = 1;
}