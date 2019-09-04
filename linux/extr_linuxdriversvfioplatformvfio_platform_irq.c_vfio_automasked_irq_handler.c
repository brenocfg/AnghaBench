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
struct vfio_platform_irq {int masked; int /*<<< orphan*/  trigger; int /*<<< orphan*/  lock; int /*<<< orphan*/  hwirq; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t vfio_automasked_irq_handler(int irq, void *dev_id)
{
	struct vfio_platform_irq *irq_ctx = dev_id;
	unsigned long flags;
	int ret = IRQ_NONE;

	spin_lock_irqsave(&irq_ctx->lock, flags);

	if (!irq_ctx->masked) {
		ret = IRQ_HANDLED;

		/* automask maskable interrupts */
		disable_irq_nosync(irq_ctx->hwirq);
		irq_ctx->masked = true;
	}

	spin_unlock_irqrestore(&irq_ctx->lock, flags);

	if (ret == IRQ_HANDLED)
		eventfd_signal(irq_ctx->trigger, 1);

	return ret;
}