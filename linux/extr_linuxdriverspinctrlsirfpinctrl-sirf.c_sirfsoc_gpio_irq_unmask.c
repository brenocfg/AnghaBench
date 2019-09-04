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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ regs; } ;
struct sirfsoc_gpio_chip {int /*<<< orphan*/  lock; TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  id; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIRFSOC_GPIO_CTL_INTR_EN_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTL_INTR_STS_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ readl (scalar_t__) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,int /*<<< orphan*/ ) ; 
 int sirfsoc_gpio_to_bankoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_gpio_irq_unmask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct sirfsoc_gpio_chip *sgpio = gpiochip_get_data(gc);
	struct sirfsoc_gpio_bank *bank = sirfsoc_gpio_to_bank(sgpio, d->hwirq);
	int idx = sirfsoc_gpio_to_bankoff(d->hwirq);
	u32 val, offset;
	unsigned long flags;

	offset = SIRFSOC_GPIO_CTRL(bank->id, idx);

	spin_lock_irqsave(&sgpio->lock, flags);

	val = readl(sgpio->chip.regs + offset);
	val &= ~SIRFSOC_GPIO_CTL_INTR_STS_MASK;
	val |= SIRFSOC_GPIO_CTL_INTR_EN_MASK;
	writel(val, sgpio->chip.regs + offset);

	spin_unlock_irqrestore(&sgpio->lock, flags);
}