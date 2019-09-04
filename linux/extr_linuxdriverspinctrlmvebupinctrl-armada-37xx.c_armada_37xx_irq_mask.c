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
typedef  int u32 ;
struct irq_data {int mask; } ;
struct gpio_chip {int dummy; } ;
struct armada_37xx_pinctrl {int base; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int IRQ_EN ; 
 int /*<<< orphan*/  armada_37xx_irq_update_reg (int*,struct irq_data*) ; 
 struct armada_37xx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readl (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void armada_37xx_irq_mask(struct irq_data *d)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	struct armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_EN;
	unsigned long flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	val = readl(info->base + reg);
	writel(val & ~d->mask, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);
}