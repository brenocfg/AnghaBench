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
struct TYPE_2__ {int /*<<< orphan*/  starting; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 scalar_t__ CRV_SENT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TCIFLUSH ; 
 int /*<<< orphan*/  T_KE ; 
 int /*<<< orphan*/  T_TE ; 
 scalar_t__ U7_SENT ; 
 int /*<<< orphan*/  check_for_codes_from_term () ; 
 scalar_t__ crv_status ; 
 int /*<<< orphan*/  cursor_on () ; 
 scalar_t__ exiting ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  mch_delay (long,scalar_t__) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_cterm_colors () ; 
 int /*<<< orphan*/  screen_start () ; 
 int /*<<< orphan*/  screen_stop_highlight () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ termcap_active ; 
 scalar_t__ u7_status ; 

void
stoptermcap()
{
    screen_stop_highlight();
    reset_cterm_colors();
    if (termcap_active)
    {
#ifdef FEAT_TERMRESPONSE
# ifdef FEAT_GUI
	if (!gui.in_use && !gui.starting)
# endif
	{
	    /* May need to discard T_CRV or T_U7 response. */
	    if (crv_status == CRV_SENT || u7_status == U7_SENT)
	    {
# ifdef UNIX
		/* Give the terminal a chance to respond. */
		mch_delay(100L, FALSE);
# endif
# ifdef TCIFLUSH
		/* Discard data received but not read. */
		if (exiting)
		    tcflush(fileno(stdin), TCIFLUSH);
# endif
	    }
	    /* Check for termcodes first, otherwise an external program may
	     * get them. */
	    check_for_codes_from_term();
	}
#endif
	out_str(T_KE);			/* stop "keypad transmit" mode */
	out_flush();
	termcap_active = FALSE;
	cursor_on();			/* just in case it is still off */
	out_str(T_TE);			/* stop termcap mode */
	screen_start();			/* don't know where cursor is now */
	out_flush();
    }
}