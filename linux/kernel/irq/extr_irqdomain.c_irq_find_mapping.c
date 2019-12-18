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
struct irq_domain {scalar_t__ revmap_direct_max_irq; scalar_t__ revmap_size; unsigned int* linear_revmap; int /*<<< orphan*/  revmap_tree; } ;
struct irq_data {scalar_t__ hwirq; unsigned int irq; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 struct irq_domain* irq_default_domain ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,scalar_t__) ; 
 struct irq_data* radix_tree_lookup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

unsigned int irq_find_mapping(struct irq_domain *domain,
			      irq_hw_number_t hwirq)
{
	struct irq_data *data;

	/* Look for default domain if nececssary */
	if (domain == NULL)
		domain = irq_default_domain;
	if (domain == NULL)
		return 0;

	if (hwirq < domain->revmap_direct_max_irq) {
		data = irq_domain_get_irq_data(domain, hwirq);
		if (data && data->hwirq == hwirq)
			return hwirq;
	}

	/* Check if the hwirq is in the linear revmap. */
	if (hwirq < domain->revmap_size)
		return domain->linear_revmap[hwirq];

	rcu_read_lock();
	data = radix_tree_lookup(&domain->revmap_tree, hwirq);
	rcu_read_unlock();
	return data ? data->irq : 0;
}