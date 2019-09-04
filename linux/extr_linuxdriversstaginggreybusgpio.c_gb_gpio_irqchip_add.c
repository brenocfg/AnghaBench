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
struct irq_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_controller {unsigned int irq_default_type; int line_max; unsigned int irq_base; int /*<<< orphan*/  irqdomain; struct irq_chip* irqchip; int /*<<< orphan*/  irq_handler; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gb_gpio_domain_ops ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,struct gpio_chip*) ; 

__attribute__((used)) static int gb_gpio_irqchip_add(struct gpio_chip *chip,
			 struct irq_chip *irqchip,
			 unsigned int first_irq,
			 irq_flow_handler_t handler,
			 unsigned int type)
{
	struct gb_gpio_controller *ggc;
	unsigned int offset;
	unsigned int irq_base;

	if (!chip || !irqchip)
		return -EINVAL;

	ggc = gpio_chip_to_gb_gpio_controller(chip);

	ggc->irqchip = irqchip;
	ggc->irq_handler = handler;
	ggc->irq_default_type = type;
	ggc->irqdomain = irq_domain_add_simple(NULL,
					ggc->line_max + 1, first_irq,
					&gb_gpio_domain_ops, chip);
	if (!ggc->irqdomain) {
		ggc->irqchip = NULL;
		return -EINVAL;
	}

	/*
	 * Prepare the mapping since the irqchip shall be orthogonal to
	 * any gpio calls. If the first_irq was zero, this is
	 * necessary to allocate descriptors for all IRQs.
	 */
	for (offset = 0; offset < (ggc->line_max + 1); offset++) {
		irq_base = irq_create_mapping(ggc->irqdomain, offset);
		if (offset == 0)
			ggc->irq_base = irq_base;
	}

	return 0;
}