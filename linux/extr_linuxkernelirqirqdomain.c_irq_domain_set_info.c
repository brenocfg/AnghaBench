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
struct irq_domain {int dummy; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,struct irq_chip*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,void*) ; 
 int /*<<< orphan*/  irq_set_handler_data (unsigned int,void*) ; 

void irq_domain_set_info(struct irq_domain *domain, unsigned int virq,
			 irq_hw_number_t hwirq, struct irq_chip *chip,
			 void *chip_data, irq_flow_handler_t handler,
			 void *handler_data, const char *handler_name)
{
	irq_set_chip_and_handler_name(virq, chip, handler, handler_name);
	irq_set_chip_data(virq, chip_data);
	irq_set_handler_data(virq, handler_data);
}