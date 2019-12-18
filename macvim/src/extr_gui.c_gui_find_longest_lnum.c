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
typedef  scalar_t__ linenr_T ;
typedef  long colnr_T ;
struct TYPE_5__ {scalar_t__ ml_line_count; } ;
struct TYPE_8__ {TYPE_1__ b_ml; } ;
struct TYPE_6__ {scalar_t__ lnum; } ;
struct TYPE_7__ {scalar_t__ w_topline; scalar_t__ w_botline; TYPE_2__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GO_HORSCROLL ; 
 scalar_t__ abs (int) ; 
 TYPE_4__* curbuf ; 
 TYPE_3__* curwin ; 
 int /*<<< orphan*/  p_go ; 
 long scroll_line_len (scalar_t__) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static linenr_T
gui_find_longest_lnum()
{
    linenr_T ret = 0;

    /* Calculate maximum for horizontal scrollbar.  Check for reasonable
     * line numbers, topline and botline can be invalid when displaying is
     * postponed. */
    if (vim_strchr(p_go, GO_HORSCROLL) == NULL
	    && curwin->w_topline <= curwin->w_cursor.lnum
	    && curwin->w_botline > curwin->w_cursor.lnum
	    && curwin->w_botline <= curbuf->b_ml.ml_line_count + 1)
    {
	linenr_T    lnum;
	colnr_T	    n;
	long	    max = 0;

	/* Use maximum of all visible lines.  Remember the lnum of the
	 * longest line, closest to the cursor line.  Used when scrolling
	 * below. */
	for (lnum = curwin->w_topline; lnum < curwin->w_botline; ++lnum)
	{
	    n = scroll_line_len(lnum);
	    if (n > (colnr_T)max)
	    {
		max = n;
		ret = lnum;
	    }
	    else if (n == (colnr_T)max
		    && abs((int)(lnum - curwin->w_cursor.lnum))
		       < abs((int)(ret - curwin->w_cursor.lnum)))
		ret = lnum;
	}
    }
    else
	/* Use cursor line only. */
	ret = curwin->w_cursor.lnum;

    return ret;
}