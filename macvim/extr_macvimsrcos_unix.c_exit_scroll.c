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
 scalar_t__ info_message ; 
 int /*<<< orphan*/  mch_errmsg (char*) ; 
 int /*<<< orphan*/  mch_msg (char*) ; 
 int /*<<< orphan*/  msg_clr_eos_force () ; 
 scalar_t__ msg_didout ; 
 scalar_t__ msg_use_printf () ; 
 scalar_t__ newline_on_exit ; 
 int /*<<< orphan*/  out_char (char) ; 
 int /*<<< orphan*/  restore_cterm_colors () ; 
 scalar_t__ silent_mode ; 
 int /*<<< orphan*/  windgoto (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
exit_scroll()
{
    if (silent_mode)
	return;
    if (newline_on_exit || msg_didout)
    {
	if (msg_use_printf())
	{
	    if (info_message)
		mch_msg("\n");
	    else
		mch_errmsg("\r\n");
	}
	else
	    out_char('\n');
    }
    else
    {
	restore_cterm_colors();		/* get original colors back */
	msg_clr_eos_force();		/* clear the rest of the display */
	windgoto((int)Rows - 1, 0);	/* may have moved the cursor */
    }
}