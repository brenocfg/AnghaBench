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
typedef  int u32 ;
struct cas {scalar_t__ lstate; scalar_t__ link_transition; int link_transition_jiffies_valid; int cas_flags; void* link_transition_jiffies; scalar_t__ regs; int /*<<< orphan*/  dev; scalar_t__ opened; } ;

/* Variables and functions */
 int CAS_FLAG_REG_PLUS ; 
 scalar_t__ LINK_TRANSITION_LINK_UP ; 
 scalar_t__ LINK_TRANSITION_ON_FAILURE ; 
 scalar_t__ LINK_TRANSITION_REQUESTED_RESET ; 
 scalar_t__ LINK_TRANSITION_STILL_FAILED ; 
 int PCS_MII_STATUS_AUTONEG_COMP ; 
 int PCS_MII_STATUS_LINK_STATUS ; 
 int PCS_MII_STATUS_REMOTE_FAULT ; 
 int PCS_SM_LINK_STATE_MASK ; 
 int PCS_SM_WORD_SYNC_STATE_MASK ; 
 scalar_t__ REG_PCS_MII_STATUS ; 
 scalar_t__ REG_PCS_SERDES_STATE ; 
 scalar_t__ REG_PCS_STATE_MACHINE ; 
 int SM_LINK_STATE_UP ; 
 int /*<<< orphan*/  cas_set_link_modes (struct cas*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ link_down ; 
 scalar_t__ link_transition_timeout ; 
 scalar_t__ link_up ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int cas_pcs_link_check(struct cas *cp)
{
	u32 stat, state_machine;
	int retval = 0;

	/* The link status bit latches on zero, so you must
	 * read it twice in such a case to see a transition
	 * to the link being up.
	 */
	stat = readl(cp->regs + REG_PCS_MII_STATUS);
	if ((stat & PCS_MII_STATUS_LINK_STATUS) == 0)
		stat = readl(cp->regs + REG_PCS_MII_STATUS);

	/* The remote-fault indication is only valid
	 * when autoneg has completed.
	 */
	if ((stat & (PCS_MII_STATUS_AUTONEG_COMP |
		     PCS_MII_STATUS_REMOTE_FAULT)) ==
	    (PCS_MII_STATUS_AUTONEG_COMP | PCS_MII_STATUS_REMOTE_FAULT))
		netif_info(cp, link, cp->dev, "PCS RemoteFault\n");

	/* work around link detection issue by querying the PCS state
	 * machine directly.
	 */
	state_machine = readl(cp->regs + REG_PCS_STATE_MACHINE);
	if ((state_machine & PCS_SM_LINK_STATE_MASK) != SM_LINK_STATE_UP) {
		stat &= ~PCS_MII_STATUS_LINK_STATUS;
	} else if (state_machine & PCS_SM_WORD_SYNC_STATE_MASK) {
		stat |= PCS_MII_STATUS_LINK_STATUS;
	}

	if (stat & PCS_MII_STATUS_LINK_STATUS) {
		if (cp->lstate != link_up) {
			if (cp->opened) {
				cp->lstate = link_up;
				cp->link_transition = LINK_TRANSITION_LINK_UP;

				cas_set_link_modes(cp);
				netif_carrier_on(cp->dev);
			}
		}
	} else if (cp->lstate == link_up) {
		cp->lstate = link_down;
		if (link_transition_timeout != 0 &&
		    cp->link_transition != LINK_TRANSITION_REQUESTED_RESET &&
		    !cp->link_transition_jiffies_valid) {
			/*
			 * force a reset, as a workaround for the
			 * link-failure problem. May want to move this to a
			 * point a bit earlier in the sequence. If we had
			 * generated a reset a short time ago, we'll wait for
			 * the link timer to check the status until a
			 * timer expires (link_transistion_jiffies_valid is
			 * true when the timer is running.)  Instead of using
			 * a system timer, we just do a check whenever the
			 * link timer is running - this clears the flag after
			 * a suitable delay.
			 */
			retval = 1;
			cp->link_transition = LINK_TRANSITION_REQUESTED_RESET;
			cp->link_transition_jiffies = jiffies;
			cp->link_transition_jiffies_valid = 1;
		} else {
			cp->link_transition = LINK_TRANSITION_ON_FAILURE;
		}
		netif_carrier_off(cp->dev);
		if (cp->opened)
			netif_info(cp, link, cp->dev, "PCS link down\n");

		/* Cassini only: if you force a mode, there can be
		 * sync problems on link down. to fix that, the following
		 * things need to be checked:
		 * 1) read serialink state register
		 * 2) read pcs status register to verify link down.
		 * 3) if link down and serial link == 0x03, then you need
		 *    to global reset the chip.
		 */
		if ((cp->cas_flags & CAS_FLAG_REG_PLUS) == 0) {
			/* should check to see if we're in a forced mode */
			stat = readl(cp->regs + REG_PCS_SERDES_STATE);
			if (stat == 0x03)
				return 1;
		}
	} else if (cp->lstate == link_down) {
		if (link_transition_timeout != 0 &&
		    cp->link_transition != LINK_TRANSITION_REQUESTED_RESET &&
		    !cp->link_transition_jiffies_valid) {
			/* force a reset, as a workaround for the
			 * link-failure problem.  May want to move
			 * this to a point a bit earlier in the
			 * sequence.
			 */
			retval = 1;
			cp->link_transition = LINK_TRANSITION_REQUESTED_RESET;
			cp->link_transition_jiffies = jiffies;
			cp->link_transition_jiffies_valid = 1;
		} else {
			cp->link_transition = LINK_TRANSITION_STILL_FAILED;
		}
	}

	return retval;
}