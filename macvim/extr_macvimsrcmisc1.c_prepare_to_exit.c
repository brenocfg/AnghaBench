#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ Rows ; 
 int /*<<< orphan*/  TMODE_COOK ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  settmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoptermcap () ; 
 int /*<<< orphan*/  windgoto (int,int /*<<< orphan*/ ) ; 

void
prepare_to_exit()
{
#if defined(SIGHUP) && defined(SIG_IGN)
    /* Ignore SIGHUP, because a dropped connection causes a read error, which
     * makes Vim exit and then handling SIGHUP causes various reentrance
     * problems. */
    signal(SIGHUP, SIG_IGN);
#endif

#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui.dying = TRUE;
	out_trash();	/* trash any pending output */
    }
    else
#endif
    {
	windgoto((int)Rows - 1, 0);

	/*
	 * Switch terminal mode back now, so messages end up on the "normal"
	 * screen (if there are two screens).
	 */
	settmode(TMODE_COOK);
#ifdef WIN3264
	if (can_end_termcap_mode(FALSE) == TRUE)
#endif
	    stoptermcap();
	out_flush();
    }
}