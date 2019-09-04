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
struct jsm_channel {int ch_mistat; int ch_c_cflag; int ch_flags; int /*<<< orphan*/  ch_flags_wait; struct jsm_board* ch_bd; } ;
struct jsm_board {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARR ; 
 int CH_CD ; 
 int CH_FCAR ; 
 int CLOCAL ; 
 int UART_MSR_DCD ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsm_carrier(struct jsm_channel *ch)
{
	struct jsm_board *bd;

	int virt_carrier = 0;
	int phys_carrier = 0;

	jsm_dbg(CARR, &ch->ch_bd->pci_dev, "start\n");

	bd = ch->ch_bd;
	if (!bd)
		return;

	if (ch->ch_mistat & UART_MSR_DCD) {
		jsm_dbg(CARR, &ch->ch_bd->pci_dev, "mistat: %x D_CD: %x\n",
			ch->ch_mistat, ch->ch_mistat & UART_MSR_DCD);
		phys_carrier = 1;
	}

	if (ch->ch_c_cflag & CLOCAL)
		virt_carrier = 1;

	jsm_dbg(CARR, &ch->ch_bd->pci_dev, "DCD: physical: %d virt: %d\n",
		phys_carrier, virt_carrier);

	/*
	 * Test for a VIRTUAL carrier transition to HIGH.
	 */
	if (((ch->ch_flags & CH_FCAR) == 0) && (virt_carrier == 1)) {

		/*
		 * When carrier rises, wake any threads waiting
		 * for carrier in the open routine.
		 */

		jsm_dbg(CARR, &ch->ch_bd->pci_dev, "carrier: virt DCD rose\n");

		if (waitqueue_active(&(ch->ch_flags_wait)))
			wake_up_interruptible(&ch->ch_flags_wait);
	}

	/*
	 * Test for a PHYSICAL carrier transition to HIGH.
	 */
	if (((ch->ch_flags & CH_CD) == 0) && (phys_carrier == 1)) {

		/*
		 * When carrier rises, wake any threads waiting
		 * for carrier in the open routine.
		 */

		jsm_dbg(CARR, &ch->ch_bd->pci_dev,
			"carrier: physical DCD rose\n");

		if (waitqueue_active(&(ch->ch_flags_wait)))
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
	if ((virt_carrier == 0) && ((ch->ch_flags & CH_CD) != 0)
			&& (phys_carrier == 0)) {
		/*
		 *	When carrier drops:
		 *
		 *	Drop carrier on all open units.
		 *
		 *	Flush queues, waking up any task waiting in the
		 *	line discipline.
		 *
		 *	Send a hangup to the control terminal.
		 *
		 *	Enable all select calls.
		 */
		if (waitqueue_active(&(ch->ch_flags_wait)))
			wake_up_interruptible(&ch->ch_flags_wait);
	}

	/*
	 *  Make sure that our cached values reflect the current reality.
	 */
	if (virt_carrier == 1)
		ch->ch_flags |= CH_FCAR;
	else
		ch->ch_flags &= ~CH_FCAR;

	if (phys_carrier == 1)
		ch->ch_flags |= CH_CD;
	else
		ch->ch_flags &= ~CH_CD;
}