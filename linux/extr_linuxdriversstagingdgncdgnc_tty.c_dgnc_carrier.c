#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ un_open_count; int /*<<< orphan*/  un_tty; } ;
struct TYPE_5__ {scalar_t__ un_open_count; int /*<<< orphan*/  un_tty; } ;
struct TYPE_4__ {int digi_flags; } ;
struct channel_t {int ch_mistat; int ch_c_cflag; int ch_flags; TYPE_3__ ch_pun; TYPE_2__ ch_tun; int /*<<< orphan*/  ch_flags_wait; TYPE_1__ ch_digi; } ;

/* Variables and functions */
 int CH_CD ; 
 int CH_FCAR ; 
 int CLOCAL ; 
 int DIGI_FORCEDCD ; 
 int UART_MSR_DCD ; 
 int /*<<< orphan*/  tty_hangup (int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void dgnc_carrier(struct channel_t *ch)
{
	int virt_carrier = 0;
	int phys_carrier = 0;

	if (!ch)
		return;

	if (ch->ch_mistat & UART_MSR_DCD)
		phys_carrier = 1;

	if (ch->ch_digi.digi_flags & DIGI_FORCEDCD)
		virt_carrier = 1;

	if (ch->ch_c_cflag & CLOCAL)
		virt_carrier = 1;

	/* Test for a VIRTUAL carrier transition to HIGH. */

	if (((ch->ch_flags & CH_FCAR) == 0) && (virt_carrier == 1)) {
		/*
		 * When carrier rises, wake any threads waiting
		 * for carrier in the open routine.
		 */
		if (waitqueue_active(&ch->ch_flags_wait))
			wake_up_interruptible(&ch->ch_flags_wait);
	}

	/* Test for a PHYSICAL carrier transition to HIGH. */

	if (((ch->ch_flags & CH_CD) == 0) && (phys_carrier == 1)) {
		/*
		 * When carrier rises, wake any threads waiting
		 * for carrier in the open routine.
		 */
		if (waitqueue_active(&ch->ch_flags_wait))
			wake_up_interruptible(&ch->ch_flags_wait);
	}

	/*
	 *  Test for a PHYSICAL transition to low, so long as we aren't
	 *  currently ignoring physical transitions (which is what "virtual
	 *  carrier" indicates).
	 *
	 *  The transition of the virtual carrier to low really doesn't
	 *  matter... it really only means "ignore carrier state", not
	 *  "make pretend that carrier is there".
	 */
	if ((virt_carrier == 0) && ((ch->ch_flags & CH_CD) != 0) &&
	    (phys_carrier == 0)) {
		/*
		 *   When carrier drops:
		 *
		 *   Drop carrier on all open units.
		 *
		 *   Flush queues, waking up any task waiting in the
		 *   line discipline.
		 *
		 *   Send a hangup to the control terminal.
		 *
		 *   Enable all select calls.
		 */
		if (waitqueue_active(&ch->ch_flags_wait))
			wake_up_interruptible(&ch->ch_flags_wait);

		if (ch->ch_tun.un_open_count > 0)
			tty_hangup(ch->ch_tun.un_tty);

		if (ch->ch_pun.un_open_count > 0)
			tty_hangup(ch->ch_pun.un_tty);
	}

	/*  Make sure that our cached values reflect the current reality. */

	if (virt_carrier == 1)
		ch->ch_flags |= CH_FCAR;
	else
		ch->ch_flags &= ~CH_FCAR;

	if (phys_carrier == 1)
		ch->ch_flags |= CH_CD;
	else
		ch->ch_flags &= ~CH_CD;
}