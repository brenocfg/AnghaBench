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
typedef  int /*<<< orphan*/  u8 ;
struct irq_data {size_t hwirq; } ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_line {int irq_type_pending; int /*<<< orphan*/  irq_type; } ;
struct gb_gpio_controller {TYPE_1__* gbphy_dev; struct gb_gpio_line* lines; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  GB_GPIO_IRQ_TYPE_NONE ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_to_gpio_chip (struct irq_data*) ; 

__attribute__((used)) static int gb_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *chip = irq_data_to_gpio_chip(d);
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	struct gb_gpio_line *line = &ggc->lines[d->hwirq];
	struct device *dev = &ggc->gbphy_dev->dev;
	u8 irq_type;

	switch (type) {
	case IRQ_TYPE_NONE:
		irq_type = GB_GPIO_IRQ_TYPE_NONE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_BOTH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irq_type = GB_GPIO_IRQ_TYPE_LEVEL_LOW;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irq_type = GB_GPIO_IRQ_TYPE_LEVEL_HIGH;
		break;
	default:
		dev_err(dev, "unsupported irq type: %u\n", type);
		return -EINVAL;
	}

	line->irq_type = irq_type;
	line->irq_type_pending = true;

	return 0;
}