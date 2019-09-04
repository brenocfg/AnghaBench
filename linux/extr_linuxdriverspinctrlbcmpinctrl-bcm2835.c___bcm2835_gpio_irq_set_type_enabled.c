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
struct bcm2835_pinctrl {unsigned int* irq_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  bcm2835_gpio_irq_config (struct bcm2835_pinctrl*,unsigned int,int) ; 

__attribute__((used)) static int __bcm2835_gpio_irq_set_type_enabled(struct bcm2835_pinctrl *pc,
	unsigned offset, unsigned int type)
{
	switch (type) {
	case IRQ_TYPE_NONE:
		if (pc->irq_type[offset] != type) {
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		}
		break;

	case IRQ_TYPE_EDGE_RISING:
		if (pc->irq_type[offset] == IRQ_TYPE_EDGE_BOTH) {
			/* RISING already enabled, disable FALLING */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_FALLING;
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		} else if (pc->irq_type[offset] != type) {
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		}
		break;

	case IRQ_TYPE_EDGE_FALLING:
		if (pc->irq_type[offset] == IRQ_TYPE_EDGE_BOTH) {
			/* FALLING already enabled, disable RISING */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_RISING;
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		} else if (pc->irq_type[offset] != type) {
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		}
		break;

	case IRQ_TYPE_EDGE_BOTH:
		if (pc->irq_type[offset] == IRQ_TYPE_EDGE_RISING) {
			/* RISING already enabled, enable FALLING too */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_FALLING;
			bcm2835_gpio_irq_config(pc, offset, true);
			pc->irq_type[offset] = type;
		} else if (pc->irq_type[offset] == IRQ_TYPE_EDGE_FALLING) {
			/* FALLING already enabled, enable RISING too */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_RISING;
			bcm2835_gpio_irq_config(pc, offset, true);
			pc->irq_type[offset] = type;
		} else if (pc->irq_type[offset] != type) {
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		}
		break;

	case IRQ_TYPE_LEVEL_HIGH:
	case IRQ_TYPE_LEVEL_LOW:
		if (pc->irq_type[offset] != type) {
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		}
		break;

	default:
		return -EINVAL;
	}
	return 0;
}