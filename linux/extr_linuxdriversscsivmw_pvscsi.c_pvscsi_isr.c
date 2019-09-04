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
struct pvscsi_adapter {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; scalar_t__ use_msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ pvscsi_msg_pending (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_completion_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pvscsi_isr(int irq, void *devp)
{
	struct pvscsi_adapter *adapter = devp;
	unsigned long flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);
	pvscsi_process_completion_ring(adapter);
	if (adapter->use_msg && pvscsi_msg_pending(adapter))
		queue_work(adapter->workqueue, &adapter->work);
	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	return IRQ_HANDLED;
}