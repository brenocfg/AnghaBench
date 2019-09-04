#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct hfa384x_usbctlx {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_flags; } ;
struct hfa384x {int req_timer_done; int resp_timer_done; TYPE_1__ ctlxq; int /*<<< orphan*/  resptimer; TYPE_2__ ctlx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLX_REQ_FAILED ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  URB_ASYNC_UNLINK ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 struct hfa384x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfa384x_usbctlx* get_active_ctlx (struct hfa384x*) ; 
 struct hfa384x* hw ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reqtimer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_2__*) ; 

__attribute__((used)) static void hfa384x_usbctlx_reqtimerfn(struct timer_list *t)
{
	struct hfa384x *hw = from_timer(hw, t, reqtimer);
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	hw->req_timer_done = 1;

	/* Removing the hardware automatically empties
	 * the active list ...
	 */
	if (!list_empty(&hw->ctlxq.active)) {
		/*
		 * We must ensure that our URB is removed from
		 * the system, if it hasn't already expired.
		 */
		hw->ctlx_urb.transfer_flags |= URB_ASYNC_UNLINK;
		if (usb_unlink_urb(&hw->ctlx_urb) == -EINPROGRESS) {
			struct hfa384x_usbctlx *ctlx = get_active_ctlx(hw);

			ctlx->state = CTLX_REQ_FAILED;

			/* This URB was active, but has now been
			 * cancelled. It will now have a status of
			 * -ECONNRESET in the callback function.
			 *
			 * We are cancelling this CTLX, so we're
			 * not going to need to wait for a response.
			 * The URB's callback function will check
			 * that this timer is truly dead.
			 */
			if (del_timer(&hw->resptimer) != 0)
				hw->resp_timer_done = 1;
		}
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
}