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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct hfa384x {TYPE_2__ ctlxq; int /*<<< orphan*/  usb_work; int /*<<< orphan*/  usb_flags; TYPE_1__* wlandev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hwremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  THROTTLE_RX ; 
 int /*<<< orphan*/  THROTTLE_TX ; 
 int /*<<< orphan*/  WORK_RX_RESUME ; 
 int /*<<< orphan*/  WORK_TX_RESUME ; 
 struct hfa384x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfa384x* hw ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throttle ; 

__attribute__((used)) static void hfa384x_usb_throttlefn(struct timer_list *t)
{
	struct hfa384x *hw = from_timer(hw, t, throttle);
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * We need to check BOTH the RX and the TX throttle controls,
	 * so we use the bitwise OR instead of the logical OR.
	 */
	pr_debug("flags=0x%lx\n", hw->usb_flags);
	if (!hw->wlandev->hwremoved &&
	    ((test_and_clear_bit(THROTTLE_RX, &hw->usb_flags) &&
	      !test_and_set_bit(WORK_RX_RESUME, &hw->usb_flags)) |
	     (test_and_clear_bit(THROTTLE_TX, &hw->usb_flags) &&
	      !test_and_set_bit(WORK_TX_RESUME, &hw->usb_flags))
	    )) {
		schedule_work(&hw->usb_work);
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
}