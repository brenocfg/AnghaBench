#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ colnr_T ;
struct TYPE_4__ {int w_leftcol; scalar_t__ w_virtcol; void* w_set_curswant; int /*<<< orphan*/  w_cursor; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int FALSE ; 
 int /*<<< orphan*/  NOT_VALID ; 
 void* TRUE ; 
 int W_WIDTH (TYPE_1__*) ; 
 int /*<<< orphan*/  changed_cline_bef_curs () ; 
 scalar_t__ coladvance (scalar_t__) ; 
 TYPE_1__* curwin ; 
 int curwin_col_off () ; 
 int /*<<< orphan*/  getvvcol (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 long p_siso ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_virtcol () ; 

int
leftcol_changed()
{
    long	lastcol;
    colnr_T	s, e;
    int		retval = FALSE;

    changed_cline_bef_curs();
    lastcol = curwin->w_leftcol + W_WIDTH(curwin) - curwin_col_off() - 1;
    validate_virtcol();

    /*
     * If the cursor is right or left of the screen, move it to last or first
     * character.
     */
    if (curwin->w_virtcol > (colnr_T)(lastcol - p_siso))
    {
	retval = TRUE;
	coladvance((colnr_T)(lastcol - p_siso));
    }
    else if (curwin->w_virtcol < curwin->w_leftcol + p_siso)
    {
	retval = TRUE;
	(void)coladvance((colnr_T)(curwin->w_leftcol + p_siso));
    }

    /*
     * If the start of the character under the cursor is not on the screen,
     * advance the cursor one more char.  If this fails (last char of the
     * line) adjust the scrolling.
     */
    getvvcol(curwin, &curwin->w_cursor, &s, NULL, &e);
    if (e > (colnr_T)lastcol)
    {
	retval = TRUE;
	coladvance(s - 1);
    }
    else if (s < curwin->w_leftcol)
    {
	retval = TRUE;
	if (coladvance(e + 1) == FAIL)	/* there isn't another character */
	{
	    curwin->w_leftcol = s;	/* adjust w_leftcol instead */
	    changed_cline_bef_curs();
	}
    }

    if (retval)
	curwin->w_set_curswant = TRUE;
    redraw_later(NOT_VALID);
    return retval;
}