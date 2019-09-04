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
struct irq_data {unsigned int hwirq; } ;
struct iproc_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPROC_GPIO_INT_DE_OFFSET ; 
 int /*<<< orphan*/  IPROC_GPIO_INT_EDGE_OFFSET ; 
 int /*<<< orphan*/  IPROC_GPIO_INT_TYPE_OFFSET ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct iproc_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  iproc_set_bit (struct iproc_gpio*,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iproc_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct iproc_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwirq;
	bool level_triggered = false;
	bool dual_edge = false;
	bool rising_or_high = false;
	unsigned long flags;

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		rising_or_high = true;
		break;

	case IRQ_TYPE_EDGE_FALLING:
		break;

	case IRQ_TYPE_EDGE_BOTH:
		dual_edge = true;
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		level_triggered = true;
		rising_or_high = true;
		break;

	case IRQ_TYPE_LEVEL_LOW:
		level_triggered = true;
		break;

	default:
		dev_err(chip->dev, "invalid GPIO IRQ type 0x%x\n",
			type);
		return -EINVAL;
	}

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_INT_TYPE_OFFSET, gpio,
		       level_triggered);
	iproc_set_bit(chip, IPROC_GPIO_INT_DE_OFFSET, gpio, dual_edge);
	iproc_set_bit(chip, IPROC_GPIO_INT_EDGE_OFFSET, gpio,
		       rising_or_high);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev,
		"gpio:%u level_triggered:%d dual_edge:%d rising_or_high:%d\n",
		gpio, level_triggered, dual_edge, rising_or_high);

	return 0;
}