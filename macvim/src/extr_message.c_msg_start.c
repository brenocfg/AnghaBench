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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 scalar_t__ Columns ; 
 scalar_t__ EXMODE_NORMAL ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  cmdline_row ; 
 scalar_t__ cmdmsg_rl ; 
 int /*<<< orphan*/  cursor_off () ; 
 scalar_t__ exmode_active ; 
 scalar_t__ full_screen ; 
 int /*<<< orphan*/ * keep_msg ; 
 scalar_t__ lines_left ; 
 int /*<<< orphan*/  msg_clr_eos () ; 
 scalar_t__ msg_col ; 
 int /*<<< orphan*/  msg_didany ; 
 int msg_didout ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  msg_row ; 
 int /*<<< orphan*/  msg_scroll ; 
 scalar_t__ msg_silent ; 
 int /*<<< orphan*/  msg_starthere () ; 
 int need_clr_eos ; 
 int /*<<< orphan*/  redir_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
msg_start()
{
    int		did_return = FALSE;

    if (!msg_silent)
    {
	vim_free(keep_msg);
	keep_msg = NULL;		/* don't display old message now */
    }

#ifdef FEAT_EVAL
    if (need_clr_eos)
    {
	/* Halfway an ":echo" command and getting an (error) message: clear
	 * any text from the command. */
	need_clr_eos = FALSE;
	msg_clr_eos();
    }
#endif

    if (!msg_scroll && full_screen)	/* overwrite last message */
    {
	msg_row = cmdline_row;
	msg_col =
#ifdef FEAT_RIGHTLEFT
	    cmdmsg_rl ? Columns - 1 :
#endif
	    0;
    }
    else if (msg_didout)		    /* start message on next line */
    {
	msg_putchar('\n');
	did_return = TRUE;
	if (exmode_active != EXMODE_NORMAL)
	    cmdline_row = msg_row;
    }
    if (!msg_didany || lines_left < 0)
	msg_starthere();
    if (msg_silent == 0)
    {
	msg_didout = FALSE;		    /* no output on current line yet */
	cursor_off();
    }

    /* when redirecting, may need to start a new line. */
    if (!did_return)
	redir_write((char_u *)"\n", -1);
}