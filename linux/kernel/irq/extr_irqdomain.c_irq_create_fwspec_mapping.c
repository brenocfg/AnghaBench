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
struct irq_fwspec {scalar_t__ fwnode; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_ANY ; 
 int /*<<< orphan*/  DOMAIN_BUS_WIRED ; 
 unsigned int IRQ_TYPE_NONE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 scalar_t__ WARN_ON (unsigned int) ; 
 int irq_create_mapping (struct irq_domain*,int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_default_domain ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_domain_alloc_irqs (struct irq_domain*,int,int /*<<< orphan*/ ,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs (int,int) ; 
 scalar_t__ irq_domain_is_hierarchy (struct irq_domain*) ; 
 scalar_t__ irq_domain_translate (struct irq_domain*,struct irq_fwspec*,int /*<<< orphan*/ *,unsigned int*) ; 
 int irq_find_mapping (struct irq_domain*,int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_find_matching_fwspec (struct irq_fwspec*,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 unsigned int irq_get_trigger_type (int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  of_node_full_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  to_of_node (scalar_t__) ; 

unsigned int irq_create_fwspec_mapping(struct irq_fwspec *fwspec)
{
	struct irq_domain *domain;
	struct irq_data *irq_data;
	irq_hw_number_t hwirq;
	unsigned int type = IRQ_TYPE_NONE;
	int virq;

	if (fwspec->fwnode) {
		domain = irq_find_matching_fwspec(fwspec, DOMAIN_BUS_WIRED);
		if (!domain)
			domain = irq_find_matching_fwspec(fwspec, DOMAIN_BUS_ANY);
	} else {
		domain = irq_default_domain;
	}

	if (!domain) {
		pr_warn("no irq domain found for %s !\n",
			of_node_full_name(to_of_node(fwspec->fwnode)));
		return 0;
	}

	if (irq_domain_translate(domain, fwspec, &hwirq, &type))
		return 0;

	/*
	 * WARN if the irqchip returns a type with bits
	 * outside the sense mask set and clear these bits.
	 */
	if (WARN_ON(type & ~IRQ_TYPE_SENSE_MASK))
		type &= IRQ_TYPE_SENSE_MASK;

	/*
	 * If we've already configured this interrupt,
	 * don't do it again, or hell will break loose.
	 */
	virq = irq_find_mapping(domain, hwirq);
	if (virq) {
		/*
		 * If the trigger type is not specified or matches the
		 * current trigger type then we are done so return the
		 * interrupt number.
		 */
		if (type == IRQ_TYPE_NONE || type == irq_get_trigger_type(virq))
			return virq;

		/*
		 * If the trigger type has not been set yet, then set
		 * it now and return the interrupt number.
		 */
		if (irq_get_trigger_type(virq) == IRQ_TYPE_NONE) {
			irq_data = irq_get_irq_data(virq);
			if (!irq_data)
				return 0;

			irqd_set_trigger_type(irq_data, type);
			return virq;
		}

		pr_warn("type mismatch, failed to map hwirq-%lu for %s!\n",
			hwirq, of_node_full_name(to_of_node(fwspec->fwnode)));
		return 0;
	}

	if (irq_domain_is_hierarchy(domain)) {
		virq = irq_domain_alloc_irqs(domain, 1, NUMA_NO_NODE, fwspec);
		if (virq <= 0)
			return 0;
	} else {
		/* Create mapping */
		virq = irq_create_mapping(domain, hwirq);
		if (!virq)
			return virq;
	}

	irq_data = irq_get_irq_data(virq);
	if (!irq_data) {
		if (irq_domain_is_hierarchy(domain))
			irq_domain_free_irqs(virq, 1);
		else
			irq_dispose_mapping(virq);
		return 0;
	}

	/* Store trigger type */
	irqd_set_trigger_type(irq_data, type);

	return virq;
}