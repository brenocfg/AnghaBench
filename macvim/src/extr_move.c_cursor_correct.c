#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int linenr_T ;
struct TYPE_7__ {int ml_line_count; } ;
struct TYPE_10__ {TYPE_1__ b_ml; } ;
struct TYPE_8__ {int lnum; } ;
struct TYPE_9__ {int w_topline; int w_height; int w_botline; int w_topfill; int w_filler_rows; int w_valid; TYPE_2__ w_cursor; } ;

/* Variables and functions */
 int VALID_CHEIGHT ; 
 int VALID_CROW ; 
 int VALID_TOPLINE ; 
 int VALID_WCOL ; 
 int VALID_WROW ; 
 TYPE_6__* curbuf ; 
 TYPE_3__* curwin ; 
 scalar_t__ diff_check_fill (TYPE_3__*,int) ; 
 int /*<<< orphan*/  hasAnyFolding (TYPE_3__*) ; 
 scalar_t__ hasFolding (int,int*,int*) ; 
 int mouse_dragging ; 
 int p_so ; 
 scalar_t__ plines (int) ; 
 scalar_t__ plines_nofill (int) ; 
 int /*<<< orphan*/  validate_botline () ; 

void
cursor_correct()
{
    int		above = 0;	    /* screen lines above topline */
    linenr_T	topline;
    int		below = 0;	    /* screen lines below botline */
    linenr_T	botline;
    int		above_wanted, below_wanted;
    linenr_T	cln;		    /* Cursor Line Number */
    int		max_off;

    /*
     * How many lines we would like to have above/below the cursor depends on
     * whether the first/last line of the file is on screen.
     */
    above_wanted = p_so;
    below_wanted = p_so;
#ifdef FEAT_MOUSE
    if (mouse_dragging > 0)
    {
	above_wanted = mouse_dragging - 1;
	below_wanted = mouse_dragging - 1;
    }
#endif
    if (curwin->w_topline == 1)
    {
	above_wanted = 0;
	max_off = curwin->w_height / 2;
	if (below_wanted > max_off)
	    below_wanted = max_off;
    }
    validate_botline();
    if (curwin->w_botline == curbuf->b_ml.ml_line_count + 1
#ifdef FEAT_MOUSE
	    && mouse_dragging == 0
#endif
	    )
    {
	below_wanted = 0;
	max_off = (curwin->w_height - 1) / 2;
	if (above_wanted > max_off)
	    above_wanted = max_off;
    }

    /*
     * If there are sufficient file-lines above and below the cursor, we can
     * return now.
     */
    cln = curwin->w_cursor.lnum;
    if (cln >= curwin->w_topline + above_wanted
	    && cln < curwin->w_botline - below_wanted
#ifdef FEAT_FOLDING
	    && !hasAnyFolding(curwin)
#endif
	    )
	return;

    /*
     * Narrow down the area where the cursor can be put by taking lines from
     * the top and the bottom until:
     * - the desired context lines are found
     * - the lines from the top is past the lines from the bottom
     */
    topline = curwin->w_topline;
    botline = curwin->w_botline - 1;
#ifdef FEAT_DIFF
    /* count filler lines as context */
    above = curwin->w_topfill;
    below = curwin->w_filler_rows;
#endif
    while ((above < above_wanted || below < below_wanted) && topline < botline)
    {
	if (below < below_wanted && (below <= above || above >= above_wanted))
	{
#ifdef FEAT_FOLDING
	    if (hasFolding(botline, &botline, NULL))
		++below;
	    else
#endif
		below += plines(botline);
	    --botline;
	}
	if (above < above_wanted && (above < below || below >= below_wanted))
	{
#ifdef FEAT_FOLDING
	    if (hasFolding(topline, NULL, &topline))
		++above;
	    else
#endif
#ifndef FEAT_DIFF
		above += plines(topline);
#else
		above += plines_nofill(topline);

	    /* Count filler lines below this line as context. */
	    if (topline < botline)
		above += diff_check_fill(curwin, topline + 1);
#endif
	    ++topline;
	}
    }
    if (topline == botline || botline == 0)
	curwin->w_cursor.lnum = topline;
    else if (topline > botline)
	curwin->w_cursor.lnum = botline;
    else
    {
	if (cln < topline && curwin->w_topline > 1)
	{
	    curwin->w_cursor.lnum = topline;
	    curwin->w_valid &=
			    ~(VALID_WROW|VALID_WCOL|VALID_CHEIGHT|VALID_CROW);
	}
	if (cln > botline && curwin->w_botline <= curbuf->b_ml.ml_line_count)
	{
	    curwin->w_cursor.lnum = botline;
	    curwin->w_valid &=
			    ~(VALID_WROW|VALID_WCOL|VALID_CHEIGHT|VALID_CROW);
	}
    }
    curwin->w_valid |= VALID_TOPLINE;
}