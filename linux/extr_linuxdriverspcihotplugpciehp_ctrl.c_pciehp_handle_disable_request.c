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
struct controller {int /*<<< orphan*/  request_result; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 129 
#define  BLINKINGON_STATE 128 
 int POWEROFF_STATE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_disable_slot (struct slot*) ; 

void pciehp_handle_disable_request(struct slot *slot)
{
	struct controller *ctrl = slot->ctrl;

	mutex_lock(&slot->lock);
	switch (slot->state) {
	case BLINKINGON_STATE:
	case BLINKINGOFF_STATE:
		cancel_delayed_work(&slot->work);
		break;
	}
	slot->state = POWEROFF_STATE;
	mutex_unlock(&slot->lock);

	ctrl->request_result = pciehp_disable_slot(slot);
}