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
struct irq_desc {int istate; scalar_t__ wake_depth; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQD_WAKEUP_STATE ; 
 int IRQS_NMI ; 
 int /*<<< orphan*/  IRQ_GET_DESC_CHECK_GLOBAL ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 struct irq_desc* irq_get_desc_buslock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_busunlock (struct irq_desc*,unsigned long) ; 
 int /*<<< orphan*/  irqd_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int set_irq_wake_real (unsigned int,unsigned int) ; 

int irq_set_irq_wake(unsigned int irq, unsigned int on)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);
	int ret = 0;

	if (!desc)
		return -EINVAL;

	/* Don't use NMIs as wake up interrupts please */
	if (desc->istate & IRQS_NMI) {
		ret = -EINVAL;
		goto out_unlock;
	}

	/* wakeup-capable irqs can be shared between drivers that
	 * don't need to have the same sleep mode behaviors.
	 */
	if (on) {
		if (desc->wake_depth++ == 0) {
			ret = set_irq_wake_real(irq, on);
			if (ret)
				desc->wake_depth = 0;
			else
				irqd_set(&desc->irq_data, IRQD_WAKEUP_STATE);
		}
	} else {
		if (desc->wake_depth == 0) {
			WARN(1, "Unbalanced IRQ %d wake disable\n", irq);
		} else if (--desc->wake_depth == 0) {
			ret = set_irq_wake_real(irq, on);
			if (ret)
				desc->wake_depth = 1;
			else
				irqd_clear(&desc->irq_data, IRQD_WAKEUP_STATE);
		}
	}

out_unlock:
	irq_put_desc_busunlock(desc, flags);
	return ret;
}