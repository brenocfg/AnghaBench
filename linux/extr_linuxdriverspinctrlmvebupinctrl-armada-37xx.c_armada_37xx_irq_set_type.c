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
struct irq_data {int hwirq; int mask; } ;
struct gpio_chip {int dummy; } ;
struct armada_37xx_pinctrl {int base; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int GPIO_PER_REG ; 
 int INPUT_VAL ; 
 int IRQ_POL ; 
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 
 int /*<<< orphan*/  armada_37xx_irq_update_reg (int*,struct irq_data*) ; 
 struct armada_37xx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readl (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int armada_37xx_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	struct armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_POL;
	unsigned long flags;

	spin_lock_irqsave(&info->irq_lock, flags);
	armada_37xx_irq_update_reg(&reg, d);
	val = readl(info->base + reg);
	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		val &= ~(BIT(d->hwirq % GPIO_PER_REG));
		break;
	case IRQ_TYPE_EDGE_FALLING:
		val |= (BIT(d->hwirq % GPIO_PER_REG));
		break;
	case IRQ_TYPE_EDGE_BOTH: {
		u32 in_val, in_reg = INPUT_VAL;

		armada_37xx_irq_update_reg(&in_reg, d);
		regmap_read(info->regmap, in_reg, &in_val);

		/* Set initial polarity based on current input level. */
		if (in_val & d->mask)
			val |= d->mask;		/* falling */
		else
			val &= ~d->mask;	/* rising */
		break;
	}
	default:
		spin_unlock_irqrestore(&info->irq_lock, flags);
		return -EINVAL;
	}
	writel(val, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);

	return 0;
}