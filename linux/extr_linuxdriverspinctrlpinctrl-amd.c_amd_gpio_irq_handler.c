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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct gpio_chip {TYPE_1__ irq; } ;
struct amd_gpio {int* base; int /*<<< orphan*/  lock; struct gpio_chip gc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EOI_MASK ; 
 int /*<<< orphan*/  INTERRUPT_MASK_OFF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PIN_IRQ_PENDING ; 
 int WAKE_INT_MASTER_REG ; 
 int WAKE_INT_STATUS_REG0 ; 
 int WAKE_INT_STATUS_REG1 ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int*) ; 
 int /*<<< orphan*/  writel (int,int*) ; 

__attribute__((used)) static irqreturn_t amd_gpio_irq_handler(int irq, void *dev_id)
{
	struct amd_gpio *gpio_dev = dev_id;
	struct gpio_chip *gc = &gpio_dev->gc;
	irqreturn_t ret = IRQ_NONE;
	unsigned int i, irqnr;
	unsigned long flags;
	u32 *regs, regval;
	u64 status, mask;

	/* Read the wake status */
	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	status = readl(gpio_dev->base + WAKE_INT_STATUS_REG1);
	status <<= 32;
	status |= readl(gpio_dev->base + WAKE_INT_STATUS_REG0);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	/* Bit 0-45 contain the relevant status bits */
	status &= (1ULL << 46) - 1;
	regs = gpio_dev->base;
	for (mask = 1, irqnr = 0; status; mask <<= 1, regs += 4, irqnr += 4) {
		if (!(status & mask))
			continue;
		status &= ~mask;

		/* Each status bit covers four pins */
		for (i = 0; i < 4; i++) {
			regval = readl(regs + i);
			if (!(regval & PIN_IRQ_PENDING) ||
			    !(regval & BIT(INTERRUPT_MASK_OFF)))
				continue;
			irq = irq_find_mapping(gc->irq.domain, irqnr + i);
			generic_handle_irq(irq);

			/* Clear interrupt.
			 * We must read the pin register again, in case the
			 * value was changed while executing
			 * generic_handle_irq() above.
			 */
			raw_spin_lock_irqsave(&gpio_dev->lock, flags);
			regval = readl(regs + i);
			writel(regval, regs + i);
			raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
			ret = IRQ_HANDLED;
		}
	}

	/* Signal EOI to the GPIO unit */
	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	regval = readl(gpio_dev->base + WAKE_INT_MASTER_REG);
	regval |= EOI_MASK;
	writel(regval, gpio_dev->base + WAKE_INT_MASTER_REG);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	return ret;
}