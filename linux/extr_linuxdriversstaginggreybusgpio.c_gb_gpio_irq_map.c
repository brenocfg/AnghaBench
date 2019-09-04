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
struct irq_domain {struct gpio_chip* host_data; } ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_controller {scalar_t__ irq_default_type; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/  irqchip; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ IRQ_TYPE_NONE ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct gb_gpio_controller*) ; 
 int /*<<< orphan*/  irq_set_irq_type (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 

__attribute__((used)) static int gb_gpio_irq_map(struct irq_domain *domain, unsigned int irq,
			   irq_hw_number_t hwirq)
{
	struct gpio_chip *chip = domain->host_data;
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	irq_set_chip_data(irq, ggc);
	irq_set_chip_and_handler(irq, ggc->irqchip, ggc->irq_handler);
	irq_set_noprobe(irq);
	/*
	 * No set-up of the hardware will happen if IRQ_TYPE_NONE
	 * is passed as default type.
	 */
	if (ggc->irq_default_type != IRQ_TYPE_NONE)
		irq_set_irq_type(irq, ggc->irq_default_type);

	return 0;
}