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
struct slot {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 131 
#define  BLINKINGON_STATE 130 
 int HZ ; 
#define  OFF_STATE 129 
#define  ON_STATE 128 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_green_led_blink (struct slot*) ; 
 int /*<<< orphan*/  pciehp_green_led_off (struct slot*) ; 
 int /*<<< orphan*/  pciehp_green_led_on (struct slot*) ; 
 int /*<<< orphan*/  pciehp_set_attention_status (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

void pciehp_handle_button_press(struct slot *p_slot)
{
	struct controller *ctrl = p_slot->ctrl;

	mutex_lock(&p_slot->lock);
	switch (p_slot->state) {
	case OFF_STATE:
	case ON_STATE:
		if (p_slot->state == ON_STATE) {
			p_slot->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl, "Slot(%s): Powering off due to button press\n",
				  slot_name(p_slot));
		} else {
			p_slot->state = BLINKINGON_STATE;
			ctrl_info(ctrl, "Slot(%s) Powering on due to button press\n",
				  slot_name(p_slot));
		}
		/* blink green LED and turn off amber */
		pciehp_green_led_blink(p_slot);
		pciehp_set_attention_status(p_slot, 0);
		schedule_delayed_work(&p_slot->work, 5 * HZ);
		break;
	case BLINKINGOFF_STATE:
	case BLINKINGON_STATE:
		/*
		 * Cancel if we are still blinking; this means that we
		 * press the attention again before the 5 sec. limit
		 * expires to cancel hot-add or hot-remove
		 */
		ctrl_info(ctrl, "Slot(%s): Button cancel\n", slot_name(p_slot));
		cancel_delayed_work(&p_slot->work);
		if (p_slot->state == BLINKINGOFF_STATE) {
			p_slot->state = ON_STATE;
			pciehp_green_led_on(p_slot);
		} else {
			p_slot->state = OFF_STATE;
			pciehp_green_led_off(p_slot);
		}
		pciehp_set_attention_status(p_slot, 0);
		ctrl_info(ctrl, "Slot(%s): Action canceled due to button press\n",
			  slot_name(p_slot));
		break;
	default:
		ctrl_err(ctrl, "Slot(%s): Ignoring invalid state %#x\n",
			 slot_name(p_slot), p_slot->state);
		break;
	}
	mutex_unlock(&p_slot->lock);
}