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
struct timer_list {int dummy; } ;
struct hfa384x_usbctlx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct hfa384x {int resp_timer_done; TYPE_1__ ctlxq; } ;

/* Variables and functions */
 struct hfa384x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfa384x_usbctlx* get_active_ctlx (struct hfa384x*) ; 
 int /*<<< orphan*/  hfa384x_usbctlxq_run (struct hfa384x*) ; 
 struct hfa384x* hw ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resptimer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlocked_usbctlx_cancel_async (struct hfa384x*,struct hfa384x_usbctlx*) ; 

__attribute__((used)) static void hfa384x_usbctlx_resptimerfn(struct timer_list *t)
{
	struct hfa384x *hw = from_timer(hw, t, resptimer);
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	hw->resp_timer_done = 1;

	/* The active list will be empty if the
	 * adapter has been unplugged ...
	 */
	if (!list_empty(&hw->ctlxq.active)) {
		struct hfa384x_usbctlx *ctlx = get_active_ctlx(hw);

		if (unlocked_usbctlx_cancel_async(hw, ctlx) == 0) {
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			hfa384x_usbctlxq_run(hw);
			return;
		}
	}
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
}