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
struct sfp {int sm_mod_state; int sm_dev_state; int sm_state; int state; int /*<<< orphan*/  sm_mutex; int /*<<< orphan*/  dev; scalar_t__ mod_phy; int /*<<< orphan*/  attached; } ;

/* Variables and functions */
 int EAGAIN ; 
 int SFP_DEV_DOWN ; 
#define  SFP_DEV_UP 139 
 unsigned int SFP_E_DEV_DOWN ; 
 unsigned int SFP_E_DEV_UP ; 
 unsigned int SFP_E_INSERT ; 
 unsigned int SFP_E_REMOVE ; 
 unsigned int SFP_E_TIMEOUT ; 
 unsigned int SFP_E_TX_CLEAR ; 
 unsigned int SFP_E_TX_FAULT ; 
 int SFP_F_TX_FAULT ; 
 int SFP_MOD_EMPTY ; 
#define  SFP_MOD_ERROR 138 
#define  SFP_MOD_HPOWER 137 
#define  SFP_MOD_PRESENT 136 
#define  SFP_MOD_PROBE 135 
#define  SFP_S_DOWN 134 
#define  SFP_S_INIT 133 
#define  SFP_S_LINK_UP 132 
#define  SFP_S_REINIT 131 
#define  SFP_S_TX_DISABLE 130 
#define  SFP_S_TX_FAULT 129 
#define  SFP_S_WAIT_LOS 128 
 int /*<<< orphan*/  T_INIT_JIFFIES ; 
 int T_PROBE_INIT ; 
 int /*<<< orphan*/  T_PROBE_RETRY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_state_to_str (int) ; 
 int /*<<< orphan*/  event_to_str (unsigned int) ; 
 int /*<<< orphan*/  mod_state_to_str (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfp_los_event_active (struct sfp*,unsigned int) ; 
 int /*<<< orphan*/  sfp_los_event_inactive (struct sfp*,unsigned int) ; 
 int /*<<< orphan*/  sfp_module_tx_disable (struct sfp*) ; 
 int /*<<< orphan*/  sfp_module_tx_fault_reset (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_fault (struct sfp*,int) ; 
 int /*<<< orphan*/  sfp_sm_ins_next (struct sfp*,int,int) ; 
 int /*<<< orphan*/  sfp_sm_link_check_los (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_link_down (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_link_up (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_mod_init (struct sfp*) ; 
 int sfp_sm_mod_probe (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_mod_remove (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_next (struct sfp*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_sm_phy_detach (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_set_timer (struct sfp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_state_to_str (int) ; 

__attribute__((used)) static void sfp_sm_event(struct sfp *sfp, unsigned int event)
{
	mutex_lock(&sfp->sm_mutex);

	dev_dbg(sfp->dev, "SM: enter %s:%s:%s event %s\n",
		mod_state_to_str(sfp->sm_mod_state),
		dev_state_to_str(sfp->sm_dev_state),
		sm_state_to_str(sfp->sm_state),
		event_to_str(event));

	/* This state machine tracks the insert/remove state of
	 * the module, and handles probing the on-board EEPROM.
	 */
	switch (sfp->sm_mod_state) {
	default:
		if (event == SFP_E_INSERT && sfp->attached) {
			sfp_module_tx_disable(sfp);
			sfp_sm_ins_next(sfp, SFP_MOD_PROBE, T_PROBE_INIT);
		}
		break;

	case SFP_MOD_PROBE:
		if (event == SFP_E_REMOVE) {
			sfp_sm_ins_next(sfp, SFP_MOD_EMPTY, 0);
		} else if (event == SFP_E_TIMEOUT) {
			int val = sfp_sm_mod_probe(sfp);

			if (val == 0)
				sfp_sm_ins_next(sfp, SFP_MOD_PRESENT, 0);
			else if (val > 0)
				sfp_sm_ins_next(sfp, SFP_MOD_HPOWER, val);
			else if (val != -EAGAIN)
				sfp_sm_ins_next(sfp, SFP_MOD_ERROR, 0);
			else
				sfp_sm_set_timer(sfp, T_PROBE_RETRY);
		}
		break;

	case SFP_MOD_HPOWER:
		if (event == SFP_E_TIMEOUT) {
			sfp_sm_ins_next(sfp, SFP_MOD_PRESENT, 0);
			break;
		}
		/* fallthrough */
	case SFP_MOD_PRESENT:
	case SFP_MOD_ERROR:
		if (event == SFP_E_REMOVE) {
			sfp_sm_mod_remove(sfp);
			sfp_sm_ins_next(sfp, SFP_MOD_EMPTY, 0);
		}
		break;
	}

	/* This state machine tracks the netdev up/down state */
	switch (sfp->sm_dev_state) {
	default:
		if (event == SFP_E_DEV_UP)
			sfp->sm_dev_state = SFP_DEV_UP;
		break;

	case SFP_DEV_UP:
		if (event == SFP_E_DEV_DOWN) {
			/* If the module has a PHY, avoid raising TX disable
			 * as this resets the PHY. Otherwise, raise it to
			 * turn the laser off.
			 */
			if (!sfp->mod_phy)
				sfp_module_tx_disable(sfp);
			sfp->sm_dev_state = SFP_DEV_DOWN;
		}
		break;
	}

	/* Some events are global */
	if (sfp->sm_state != SFP_S_DOWN &&
	    (sfp->sm_mod_state != SFP_MOD_PRESENT ||
	     sfp->sm_dev_state != SFP_DEV_UP)) {
		if (sfp->sm_state == SFP_S_LINK_UP &&
		    sfp->sm_dev_state == SFP_DEV_UP)
			sfp_sm_link_down(sfp);
		if (sfp->mod_phy)
			sfp_sm_phy_detach(sfp);
		sfp_sm_next(sfp, SFP_S_DOWN, 0);
		mutex_unlock(&sfp->sm_mutex);
		return;
	}

	/* The main state machine */
	switch (sfp->sm_state) {
	case SFP_S_DOWN:
		if (sfp->sm_mod_state == SFP_MOD_PRESENT &&
		    sfp->sm_dev_state == SFP_DEV_UP)
			sfp_sm_mod_init(sfp);
		break;

	case SFP_S_INIT:
		if (event == SFP_E_TIMEOUT && sfp->state & SFP_F_TX_FAULT)
			sfp_sm_fault(sfp, true);
		else if (event == SFP_E_TIMEOUT || event == SFP_E_TX_CLEAR)
			sfp_sm_link_check_los(sfp);
		break;

	case SFP_S_WAIT_LOS:
		if (event == SFP_E_TX_FAULT)
			sfp_sm_fault(sfp, true);
		else if (sfp_los_event_inactive(sfp, event))
			sfp_sm_link_up(sfp);
		break;

	case SFP_S_LINK_UP:
		if (event == SFP_E_TX_FAULT) {
			sfp_sm_link_down(sfp);
			sfp_sm_fault(sfp, true);
		} else if (sfp_los_event_active(sfp, event)) {
			sfp_sm_link_down(sfp);
			sfp_sm_next(sfp, SFP_S_WAIT_LOS, 0);
		}
		break;

	case SFP_S_TX_FAULT:
		if (event == SFP_E_TIMEOUT) {
			sfp_module_tx_fault_reset(sfp);
			sfp_sm_next(sfp, SFP_S_REINIT, T_INIT_JIFFIES);
		}
		break;

	case SFP_S_REINIT:
		if (event == SFP_E_TIMEOUT && sfp->state & SFP_F_TX_FAULT) {
			sfp_sm_fault(sfp, false);
		} else if (event == SFP_E_TIMEOUT || event == SFP_E_TX_CLEAR) {
			dev_info(sfp->dev, "module transmit fault recovered\n");
			sfp_sm_link_check_los(sfp);
		}
		break;

	case SFP_S_TX_DISABLE:
		break;
	}

	dev_dbg(sfp->dev, "SM: exit %s:%s:%s\n",
		mod_state_to_str(sfp->sm_mod_state),
		dev_state_to_str(sfp->sm_dev_state),
		sm_state_to_str(sfp->sm_state));

	mutex_unlock(&sfp->sm_mutex);
}