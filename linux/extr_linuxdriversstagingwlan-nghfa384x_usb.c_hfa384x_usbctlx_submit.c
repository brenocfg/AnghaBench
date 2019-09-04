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
struct hfa384x_usbctlx {int /*<<< orphan*/  list; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; } ;
struct hfa384x {TYPE_2__ ctlxq; TYPE_1__* wlandev; } ;
struct TYPE_3__ {scalar_t__ hwremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLX_PENDING ; 
 int ENODEV ; 
 int /*<<< orphan*/  hfa384x_usbctlxq_run (struct hfa384x*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hfa384x_usbctlx_submit(struct hfa384x *hw,
				  struct hfa384x_usbctlx *ctlx)
{
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	if (hw->wlandev->hwremoved) {
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		return -ENODEV;
	}

	ctlx->state = CTLX_PENDING;
	list_add_tail(&ctlx->list, &hw->ctlxq.pending);
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
	hfa384x_usbctlxq_run(hw);

	return 0;
}