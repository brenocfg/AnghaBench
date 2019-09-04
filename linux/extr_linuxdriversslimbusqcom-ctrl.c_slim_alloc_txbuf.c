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
struct slim_msg_txn {int dummy; } ;
struct TYPE_2__ {int head; int n; int tail; void* base; int sl_sz; int /*<<< orphan*/  lock; } ;
struct qcom_slim_ctrl {TYPE_1__ tx; struct completion** wr_comp; int /*<<< orphan*/  dev; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void *slim_alloc_txbuf(struct qcom_slim_ctrl *ctrl,
			      struct slim_msg_txn *txn,
			      struct completion *done)
{
	unsigned long flags;
	int idx;

	spin_lock_irqsave(&ctrl->tx.lock, flags);
	if (((ctrl->tx.head + 1) % ctrl->tx.n) == ctrl->tx.tail) {
		spin_unlock_irqrestore(&ctrl->tx.lock, flags);
		dev_err(ctrl->dev, "controller TX buf unavailable");
		return NULL;
	}
	idx = ctrl->tx.tail;
	ctrl->wr_comp[idx] = done;
	ctrl->tx.tail = (ctrl->tx.tail + 1) % ctrl->tx.n;

	spin_unlock_irqrestore(&ctrl->tx.lock, flags);

	return ctrl->tx.base + (idx * ctrl->tx.sl_sz);
}