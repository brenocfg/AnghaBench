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
typedef  int u32 ;
struct TYPE_2__ {int regs; } ;
struct sirfsoc_gpio_chip {int /*<<< orphan*/  lock; TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  id; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 int SIRFSOC_GPIO_CTL_INTR_HIGH_MASK ; 
 int SIRFSOC_GPIO_CTL_INTR_LOW_MASK ; 
 int SIRFSOC_GPIO_CTL_INTR_STS_MASK ; 
 int SIRFSOC_GPIO_CTL_INTR_TYPE_MASK ; 
 int SIRFSOC_GPIO_CTL_OUT_EN_MASK ; 
 int SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readl (int) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,int /*<<< orphan*/ ) ; 
 int sirfsoc_gpio_to_bankoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int sirfsoc_gpio_irq_type(struct irq_data *d, unsigned type)
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
	val &= ~(SIRFSOC_GPIO_CTL_INTR_STS_MASK | SIRFSOC_GPIO_CTL_OUT_EN_MASK);

	switch (type) {
	case IRQ_TYPE_NONE:
		break;
	case IRQ_TYPE_EDGE_RISING:
		val |= SIRFSOC_GPIO_CTL_INTR_HIGH_MASK |
			SIRFSOC_GPIO_CTL_INTR_TYPE_MASK;
		val &= ~SIRFSOC_GPIO_CTL_INTR_LOW_MASK;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		val &= ~SIRFSOC_GPIO_CTL_INTR_HIGH_MASK;
		val |= SIRFSOC_GPIO_CTL_INTR_LOW_MASK |
			SIRFSOC_GPIO_CTL_INTR_TYPE_MASK;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		val |= SIRFSOC_GPIO_CTL_INTR_HIGH_MASK |
			SIRFSOC_GPIO_CTL_INTR_LOW_MASK |
			SIRFSOC_GPIO_CTL_INTR_TYPE_MASK;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		val &= ~(SIRFSOC_GPIO_CTL_INTR_HIGH_MASK |
			SIRFSOC_GPIO_CTL_INTR_TYPE_MASK);
		val |= SIRFSOC_GPIO_CTL_INTR_LOW_MASK;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		val |= SIRFSOC_GPIO_CTL_INTR_HIGH_MASK;
		val &= ~(SIRFSOC_GPIO_CTL_INTR_LOW_MASK |
			SIRFSOC_GPIO_CTL_INTR_TYPE_MASK);
		break;
	}

	writel(val, sgpio->chip.regs + offset);

	spin_unlock_irqrestore(&sgpio->lock, flags);

	return 0;
}