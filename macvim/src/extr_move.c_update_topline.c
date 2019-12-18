#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {long lnum; scalar_t__ fill; scalar_t__ height; } ;
typedef  TYPE_3__ lineoff_T ;
typedef  long linenr_T ;
struct TYPE_10__ {long ml_line_count; } ;
struct TYPE_14__ {TYPE_1__ b_ml; } ;
struct TYPE_11__ {int lnum; } ;
struct TYPE_13__ {int w_valid; long w_topline; int w_topfill; int w_botline; int w_scbind_pos; int w_height; int w_empty_rows; scalar_t__ w_skipcol; TYPE_2__ w_cursor; scalar_t__ w_filler_rows; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  NOT_VALID ; 
 int TRUE ; 
 int /*<<< orphan*/  VALID ; 
 int VALID_BOTLINE ; 
 int VALID_BOTLINE_AP ; 
 int VALID_TOPLINE ; 
 int /*<<< orphan*/  botline_forw (TYPE_3__*) ; 
 scalar_t__ bufempty () ; 
 int /*<<< orphan*/  check_cursor_moved (TYPE_4__*) ; 
 scalar_t__ check_top_offset () ; 
 TYPE_7__* curbuf ; 
 TYPE_4__* curwin ; 
 int diff_check_fill (TYPE_4__*,int) ; 
 int dollar_vcol ; 
 scalar_t__ hasAnyFolding (TYPE_4__*) ; 
 int /*<<< orphan*/  hasFolding (long,long*,long*) ; 
 int mouse_dragging ; 
 long p_so ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_valid (int) ; 
 int /*<<< orphan*/  scroll_cursor_bot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scroll_cursor_halfway (int) ; 
 int /*<<< orphan*/  scroll_cursor_top (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scrolljump_value () ; 
 int /*<<< orphan*/  validate_botline () ; 
 int /*<<< orphan*/  validate_cursor () ; 

void
update_topline()
{
    long	line_count;
    int		halfheight;
    int		n;
    linenr_T	old_topline;
#ifdef FEAT_DIFF
    int		old_topfill;
#endif
#ifdef FEAT_FOLDING
    linenr_T	lnum;
#endif
    int		check_topline = FALSE;
    int		check_botline = FALSE;
#ifdef FEAT_MOUSE
    int		save_so = p_so;
#endif

    if (!screen_valid(TRUE))
	return;

    check_cursor_moved(curwin);
    if (curwin->w_valid & VALID_TOPLINE)
	return;

#ifdef FEAT_MOUSE
    /* When dragging with the mouse, don't scroll that quickly */
    if (mouse_dragging > 0)
	p_so = mouse_dragging - 1;
#endif

    old_topline = curwin->w_topline;
#ifdef FEAT_DIFF
    old_topfill = curwin->w_topfill;
#endif

    /*
     * If the buffer is empty, always set topline to 1.
     */
    if (bufempty())		/* special case - file is empty */
    {
	if (curwin->w_topline != 1)
	    redraw_later(NOT_VALID);
	curwin->w_topline = 1;
	curwin->w_botline = 2;
	curwin->w_valid |= VALID_BOTLINE|VALID_BOTLINE_AP;
#ifdef FEAT_SCROLLBIND
	curwin->w_scbind_pos = 1;
#endif
    }

    /*
     * If the cursor is above or near the top of the window, scroll the window
     * to show the line the cursor is in, with 'scrolloff' context.
     */
    else
    {
	if (curwin->w_topline > 1)
	{
	    /* If the cursor is above topline, scrolling is always needed.
	     * If the cursor is far below topline and there is no folding,
	     * scrolling down is never needed. */
	    if (curwin->w_cursor.lnum < curwin->w_topline)
		check_topline = TRUE;
	    else if (check_top_offset())
		check_topline = TRUE;
	}
#ifdef FEAT_DIFF
	    /* Check if there are more filler lines than allowed. */
	if (!check_topline && curwin->w_topfill > diff_check_fill(curwin,
							   curwin->w_topline))
	    check_topline = TRUE;
#endif

	if (check_topline)
	{
	    halfheight = curwin->w_height / 2 - 1;
	    if (halfheight < 2)
		halfheight = 2;

#ifdef FEAT_FOLDING
	    if (hasAnyFolding(curwin))
	    {
		/* Count the number of logical lines between the cursor and
		 * topline + p_so (approximation of how much will be
		 * scrolled). */
		n = 0;
		for (lnum = curwin->w_cursor.lnum;
				      lnum < curwin->w_topline + p_so; ++lnum)
		{
		    ++n;
		    /* stop at end of file or when we know we are far off */
		    if (lnum >= curbuf->b_ml.ml_line_count || n >= halfheight)
			break;
		    (void)hasFolding(lnum, NULL, &lnum);
		}
	    }
	    else
#endif
		n = curwin->w_topline + p_so - curwin->w_cursor.lnum;

	    /* If we weren't very close to begin with, we scroll to put the
	     * cursor in the middle of the window.  Otherwise put the cursor
	     * near the top of the window. */
	    if (n >= halfheight)
		scroll_cursor_halfway(FALSE);
	    else
	    {
		scroll_cursor_top(scrolljump_value(), FALSE);
		check_botline = TRUE;
	    }
	}

	else
	{
#ifdef FEAT_FOLDING
	    /* Make sure topline is the first line of a fold. */
	    (void)hasFolding(curwin->w_topline, &curwin->w_topline, NULL);
#endif
	    check_botline = TRUE;
	}
    }

    /*
     * If the cursor is below the bottom of the window, scroll the window
     * to put the cursor on the window.
     * When w_botline is invalid, recompute it first, to avoid a redraw later.
     * If w_botline was approximated, we might need a redraw later in a few
     * cases, but we don't want to spend (a lot of) time recomputing w_botline
     * for every small change.
     */
    if (check_botline)
    {
	if (!(curwin->w_valid & VALID_BOTLINE_AP))
	    validate_botline();

	if (curwin->w_botline <= curbuf->b_ml.ml_line_count)
	{
	    if (curwin->w_cursor.lnum < curwin->w_botline)
	    {
	      if (((long)curwin->w_cursor.lnum
					     >= (long)curwin->w_botline - p_so
#ifdef FEAT_FOLDING
			|| hasAnyFolding(curwin)
#endif
			))
	      {
		lineoff_T	loff;

		/* Cursor is (a few lines) above botline, check if there are
		 * 'scrolloff' window lines below the cursor.  If not, need to
		 * scroll. */
		n = curwin->w_empty_rows;
		loff.lnum = curwin->w_cursor.lnum;
#ifdef FEAT_FOLDING
		/* In a fold go to its last line. */
		(void)hasFolding(loff.lnum, NULL, &loff.lnum);
#endif
#ifdef FEAT_DIFF
		loff.fill = 0;
		n += curwin->w_filler_rows;
#endif
		loff.height = 0;
		while (loff.lnum < curwin->w_botline
#ifdef FEAT_DIFF
			&& (loff.lnum + 1 < curwin->w_botline || loff.fill == 0)
#endif
			)
		{
		    n += loff.height;
		    if (n >= p_so)
			break;
		    botline_forw(&loff);
		}
		if (n >= p_so)
		    /* sufficient context, no need to scroll */
		    check_botline = FALSE;
	      }
	      else
		  /* sufficient context, no need to scroll */
		  check_botline = FALSE;
	    }
	    if (check_botline)
	    {
#ifdef FEAT_FOLDING
		if (hasAnyFolding(curwin))
		{
		    /* Count the number of logical lines between the cursor and
		     * botline - p_so (approximation of how much will be
		     * scrolled). */
		    line_count = 0;
		    for (lnum = curwin->w_cursor.lnum;
				     lnum >= curwin->w_botline - p_so; --lnum)
		    {
			++line_count;
			/* stop at end of file or when we know we are far off */
			if (lnum <= 0 || line_count > curwin->w_height + 1)
			    break;
			(void)hasFolding(lnum, &lnum, NULL);
		    }
		}
		else
#endif
		    line_count = curwin->w_cursor.lnum - curwin->w_botline
								   + 1 + p_so;
		if (line_count <= curwin->w_height + 1)
		    scroll_cursor_bot(scrolljump_value(), FALSE);
		else
		    scroll_cursor_halfway(FALSE);
	    }
	}
    }
    curwin->w_valid |= VALID_TOPLINE;

    /*
     * Need to redraw when topline changed.
     */
    if (curwin->w_topline != old_topline
#ifdef FEAT_DIFF
	    || curwin->w_topfill != old_topfill
#endif
	    )
    {
	dollar_vcol = -1;
	if (curwin->w_skipcol != 0)
	{
	    curwin->w_skipcol = 0;
	    redraw_later(NOT_VALID);
	}
	else
	    redraw_later(VALID);
	/* May need to set w_skipcol when cursor in w_topline. */
	if (curwin->w_cursor.lnum == curwin->w_topline)
	    validate_cursor();
    }

#ifdef FEAT_MOUSE
    p_so = save_so;
#endif
}