#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ml_line_count; } ;
struct TYPE_7__ {TYPE_1__ b_ml; } ;
struct TYPE_6__ {scalar_t__ w_topline; scalar_t__ w_topfill; int w_wrow; scalar_t__ w_width; int w_virtcol; int w_valid; int /*<<< orphan*/  w_botline; scalar_t__ w_p_wrap; } ;

/* Variables and functions */
 int VALID_BOTLINE ; 
 int VALID_CROW ; 
 int VALID_WROW ; 
 int W_WIDTH (TYPE_2__*) ; 
 TYPE_3__* curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  hasFolding (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int p_so ; 
 int plines (scalar_t__) ; 
 int plines_nofill (scalar_t__) ; 
 int /*<<< orphan*/  validate_cursor () ; 
 int /*<<< orphan*/  validate_virtcol () ; 

void
scrollup_clamp()
{
    int	    start_row;

    if (curwin->w_topline == curbuf->b_ml.ml_line_count
#ifdef FEAT_DIFF
	    && curwin->w_topfill == 0
#endif
	    )
	return;

    validate_cursor();	    /* w_wrow needs to be valid */

    /*
     * Compute the row number of the first row of the cursor line
     * and make sure it doesn't go off the screen. Make sure the cursor
     * doesn't go before 'scrolloff' lines from the screen start.
     */
#ifdef FEAT_DIFF
    start_row = curwin->w_wrow - plines_nofill(curwin->w_topline)
							  - curwin->w_topfill;
#else
    start_row = curwin->w_wrow - plines(curwin->w_topline);
#endif
    if (curwin->w_p_wrap
#ifdef FEAT_VERTSPLIT
		&& curwin->w_width != 0
#endif
	    )
    {
	validate_virtcol();
	start_row -= curwin->w_virtcol / W_WIDTH(curwin);
    }
    if (start_row >= p_so)
    {
#ifdef FEAT_DIFF
	if (curwin->w_topfill > 0)
	    --curwin->w_topfill;
	else
#endif
	{
#ifdef FEAT_FOLDING
	    (void)hasFolding(curwin->w_topline, NULL, &curwin->w_topline);
#endif
	    ++curwin->w_topline;
	}
	++curwin->w_botline;		/* approximate w_botline */
	curwin->w_valid &= ~(VALID_WROW|VALID_CROW|VALID_BOTLINE);
    }
}