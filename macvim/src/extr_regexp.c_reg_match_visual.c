#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ lnum; scalar_t__ col; } ;
struct TYPE_15__ {TYPE_3__ w_cursor; } ;
typedef  TYPE_2__ win_T ;
typedef  TYPE_3__ pos_T ;
typedef  scalar_t__ linenr_T ;
typedef  scalar_t__ colnr_T ;
struct TYPE_14__ {int vi_mode; TYPE_3__ vi_start; TYPE_3__ vi_end; } ;
struct TYPE_17__ {TYPE_1__ b_visual; } ;

/* Variables and functions */
 int Ctrl_V ; 
 int FALSE ; 
 scalar_t__ MAXCOL ; 
 int TRUE ; 
 TYPE_3__ VIsual ; 
 scalar_t__ VIsual_active ; 
 int VIsual_mode ; 
 TYPE_6__* curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  getvvcol (TYPE_2__*,TYPE_3__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ lt (TYPE_3__,TYPE_3__) ; 
 char* p_sel ; 
 TYPE_6__* reg_buf ; 
 scalar_t__ reg_firstlnum ; 
 TYPE_2__* reg_win ; 
 scalar_t__ reginput ; 
 scalar_t__ regline ; 
 scalar_t__ reglnum ; 
 scalar_t__ win_linetabsize (TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
reg_match_visual()
{
    pos_T	top, bot;
    linenr_T    lnum;
    colnr_T	col;
    win_T	*wp = reg_win == NULL ? curwin : reg_win;
    int		mode;
    colnr_T	start, end;
    colnr_T	start2, end2;
    colnr_T	cols;

    /* Check if the buffer is the current buffer. */
    if (reg_buf != curbuf || VIsual.lnum == 0)
	return FALSE;

    if (VIsual_active)
    {
	if (lt(VIsual, wp->w_cursor))
	{
	    top = VIsual;
	    bot = wp->w_cursor;
	}
	else
	{
	    top = wp->w_cursor;
	    bot = VIsual;
	}
	mode = VIsual_mode;
    }
    else
    {
	if (lt(curbuf->b_visual.vi_start, curbuf->b_visual.vi_end))
	{
	    top = curbuf->b_visual.vi_start;
	    bot = curbuf->b_visual.vi_end;
	}
	else
	{
	    top = curbuf->b_visual.vi_end;
	    bot = curbuf->b_visual.vi_start;
	}
	mode = curbuf->b_visual.vi_mode;
    }
    lnum = reglnum + reg_firstlnum;
    if (lnum < top.lnum || lnum > bot.lnum)
	return FALSE;

    if (mode == 'v')
    {
	col = (colnr_T)(reginput - regline);
	if ((lnum == top.lnum && col < top.col)
		|| (lnum == bot.lnum && col >= bot.col + (*p_sel != 'e')))
	    return FALSE;
    }
    else if (mode == Ctrl_V)
    {
	getvvcol(wp, &top, &start, NULL, &end);
	getvvcol(wp, &bot, &start2, NULL, &end2);
	if (start2 < start)
	    start = start2;
	if (end2 > end)
	    end = end2;
	if (top.col == MAXCOL || bot.col == MAXCOL)
	    end = MAXCOL;
	cols = win_linetabsize(wp, regline, (colnr_T)(reginput - regline));
	if (cols < start || cols > end - (*p_sel == 'e'))
	    return FALSE;
    }
    return TRUE;
}