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
struct TYPE_2__ {scalar_t__ in_use; scalar_t__ starting; } ;

/* Variables and functions */
 scalar_t__ CLEAR ; 
 scalar_t__ Columns ; 
 void* FALSE ; 
 int /*<<< orphan*/ * LineOffset ; 
 void** LineWraps ; 
 scalar_t__ NOT_VALID ; 
 scalar_t__ NO_SCREEN ; 
 int Rows ; 
 int /*<<< orphan*/ * ScreenLines ; 
 void* TRUE ; 
 int /*<<< orphan*/  T_CL ; 
 scalar_t__ can_clear (int /*<<< orphan*/ ) ; 
 void* clear_cmdline ; 
 int /*<<< orphan*/  clip_scroll_selection (int) ; 
 int /*<<< orphan*/  cmdline_row ; 
 int /*<<< orphan*/  compute_cmdrow () ; 
 int /*<<< orphan*/  firstwin ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  lineclear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lineinvalid (int /*<<< orphan*/ ,int) ; 
 void* mode_displayed ; 
 scalar_t__ msg_col ; 
 void* msg_didany ; 
 void* msg_didout ; 
 int /*<<< orphan*/  msg_row ; 
 scalar_t__ msg_scrolled ; 
 scalar_t__ must_redraw ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 
 void* redraw_cmdline ; 
 void* redraw_tabline ; 
 int screen_attr ; 
 void* screen_cleared ; 
 int /*<<< orphan*/  screen_start () ; 
 int /*<<< orphan*/  screen_stop_highlight () ; 
 scalar_t__ starting ; 
 int /*<<< orphan*/  win_rest_invalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
screenclear2()
{
    int	    i;

    if (starting == NO_SCREEN || ScreenLines == NULL
#ifdef FEAT_GUI
	    || (gui.in_use && gui.starting)
#endif
	    )
	return;

#ifdef FEAT_GUI
    if (!gui.in_use)
#endif
	screen_attr = -1;	/* force setting the Normal colors */
    screen_stop_highlight();	/* don't want highlighting here */

#ifdef FEAT_CLIPBOARD
    /* disable selection without redrawing it */
    clip_scroll_selection(9999);
#endif

    /* blank out ScreenLines */
    for (i = 0; i < Rows; ++i)
    {
	lineclear(LineOffset[i], (int)Columns);
	LineWraps[i] = FALSE;
    }

    if (can_clear(T_CL))
    {
	out_str(T_CL);		/* clear the display */
	clear_cmdline = FALSE;
	mode_displayed = FALSE;
    }
    else
    {
	/* can't clear the screen, mark all chars with invalid attributes */
	for (i = 0; i < Rows; ++i)
	    lineinvalid(LineOffset[i], (int)Columns);
	clear_cmdline = TRUE;
    }

    screen_cleared = TRUE;	/* can use contents of ScreenLines now */

    win_rest_invalid(firstwin);
    redraw_cmdline = TRUE;
#ifdef FEAT_WINDOWS
    redraw_tabline = TRUE;
#endif
    if (must_redraw == CLEAR)	/* no need to clear again */
	must_redraw = NOT_VALID;
    compute_cmdrow();
    msg_row = cmdline_row;	/* put cursor on last line for messages */
    msg_col = 0;
    screen_start();		/* don't know where cursor is now */
    msg_scrolled = 0;		/* can't scroll back */
    msg_didany = FALSE;
    msg_didout = FALSE;
}