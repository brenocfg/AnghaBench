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
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  T_KS ; 
 int /*<<< orphan*/  T_TI ; 
 int /*<<< orphan*/  check_for_codes_from_term () ; 
 scalar_t__ crv_status ; 
 scalar_t__ full_screen ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  may_req_termresponse () ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_start () ; 
 scalar_t__ termcap_active ; 

void
starttermcap()
{
    if (full_screen && !termcap_active)
    {
	out_str(T_TI);			/* start termcap mode */
	out_str(T_KS);			/* start "keypad transmit" mode */
	out_flush();
	termcap_active = TRUE;
	screen_start();			/* don't know where cursor is now */
#ifdef FEAT_TERMRESPONSE
# ifdef FEAT_GUI
	if (!gui.in_use && !gui.starting)
# endif
	{
	    may_req_termresponse();
	    /* Immediately check for a response.  If t_Co changes, we don't
	     * want to redraw with wrong colors first. */
	    if (crv_status == CRV_SENT)
		check_for_codes_from_term();
	}
#endif
    }
}