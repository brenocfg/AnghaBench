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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct slot {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; struct controller* ctrl; } ;
struct controller {int /*<<< orphan*/  request_result; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 131 
#define  BLINKINGON_STATE 130 
#define  OFF_STATE 129 
#define  ON_STATE 128 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int POWEROFF_STATE ; 
 int POWERON_STATE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pciehp_check_link_active (struct controller*) ; 
 int /*<<< orphan*/  pciehp_disable_slot (struct slot*) ; 
 int /*<<< orphan*/  pciehp_enable_slot (struct slot*) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,scalar_t__*) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

void pciehp_handle_presence_or_link_change(struct slot *slot, u32 events)
{
	struct controller *ctrl = slot->ctrl;
	bool link_active;
	u8 present;

	/*
	 * If the slot is on and presence or link has changed, turn it off.
	 * Even if it's occupied again, we cannot assume the card is the same.
	 */
	mutex_lock(&slot->lock);
	switch (slot->state) {
	case BLINKINGOFF_STATE:
		cancel_delayed_work(&slot->work);
		/* fall through */
	case ON_STATE:
		slot->state = POWEROFF_STATE;
		mutex_unlock(&slot->lock);
		if (events & PCI_EXP_SLTSTA_DLLSC)
			ctrl_info(ctrl, "Slot(%s): Link Down\n",
				  slot_name(slot));
		if (events & PCI_EXP_SLTSTA_PDC)
			ctrl_info(ctrl, "Slot(%s): Card not present\n",
				  slot_name(slot));
		pciehp_disable_slot(slot);
		break;
	default:
		mutex_unlock(&slot->lock);
		break;
	}

	/* Turn the slot on if it's occupied or link is up */
	mutex_lock(&slot->lock);
	pciehp_get_adapter_status(slot, &present);
	link_active = pciehp_check_link_active(ctrl);
	if (!present && !link_active) {
		mutex_unlock(&slot->lock);
		return;
	}

	switch (slot->state) {
	case BLINKINGON_STATE:
		cancel_delayed_work(&slot->work);
		/* fall through */
	case OFF_STATE:
		slot->state = POWERON_STATE;
		mutex_unlock(&slot->lock);
		if (present)
			ctrl_info(ctrl, "Slot(%s): Card present\n",
				  slot_name(slot));
		if (link_active)
			ctrl_info(ctrl, "Slot(%s): Link Up\n",
				  slot_name(slot));
		ctrl->request_result = pciehp_enable_slot(slot);
		break;
	default:
		mutex_unlock(&slot->lock);
		break;
	}
}