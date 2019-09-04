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
struct uwb_rc {scalar_t__ set_drp_ie_pending; int /*<<< orphan*/  rsvs_lock; int /*<<< orphan*/  rsv_update_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_queue_update (struct uwb_rc*) ; 

void uwb_rsv_sched_update(struct uwb_rc *rc)
{
	spin_lock_irq(&rc->rsvs_lock);
	if (!delayed_work_pending(&rc->rsv_update_work)) {
		if (rc->set_drp_ie_pending > 0) {
			rc->set_drp_ie_pending++;
			goto unlock;
		}
		uwb_rsv_queue_update(rc);
	}
unlock:
	spin_unlock_irq(&rc->rsvs_lock);
}