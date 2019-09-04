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
struct slot {int state; int /*<<< orphan*/  lock; struct controller* ctrl; } ;
struct controller {int request_result; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  requester; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 133 
#define  BLINKINGON_STATE 132 
 int /*<<< orphan*/  DISABLE_SLOT ; 
 int ENODEV ; 
#define  OFF_STATE 131 
#define  ON_STATE 130 
#define  POWEROFF_STATE 129 
#define  POWERON_STATE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_request (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int pciehp_sysfs_disable_slot(struct slot *p_slot)
{
	struct controller *ctrl = p_slot->ctrl;

	mutex_lock(&p_slot->lock);
	switch (p_slot->state) {
	case BLINKINGOFF_STATE:
	case ON_STATE:
		mutex_unlock(&p_slot->lock);
		pciehp_request(ctrl, DISABLE_SLOT);
		wait_event(ctrl->requester,
			   !atomic_read(&ctrl->pending_events));
		return ctrl->request_result;
	case POWEROFF_STATE:
		ctrl_info(ctrl, "Slot(%s): Already in powering off state\n",
			  slot_name(p_slot));
		break;
	case BLINKINGON_STATE:
	case OFF_STATE:
	case POWERON_STATE:
		ctrl_info(ctrl, "Slot(%s): Already disabled\n",
			  slot_name(p_slot));
		break;
	default:
		ctrl_err(ctrl, "Slot(%s): Invalid state %#x\n",
			 slot_name(p_slot), p_slot->state);
		break;
	}
	mutex_unlock(&p_slot->lock);

	return -ENODEV;
}