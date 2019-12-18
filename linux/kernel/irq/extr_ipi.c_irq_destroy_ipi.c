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
struct irq_domain {int dummy; } ;
struct irq_data {TYPE_1__* common; struct irq_domain* domain; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {unsigned int ipi_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int cpumask_first (struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_subset (struct cpumask const*,struct cpumask*) ; 
 unsigned int cpumask_weight (struct cpumask const*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_is_ipi (struct irq_domain*) ; 
 scalar_t__ irq_domain_is_ipi_per_cpu (struct irq_domain*) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int irq_destroy_ipi(unsigned int irq, const struct cpumask *dest)
{
	struct irq_data *data = irq_get_irq_data(irq);
	struct cpumask *ipimask = data ? irq_data_get_affinity_mask(data) : NULL;
	struct irq_domain *domain;
	unsigned int nr_irqs;

	if (!irq || !data || !ipimask)
		return -EINVAL;

	domain = data->domain;
	if (WARN_ON(domain == NULL))
		return -EINVAL;

	if (!irq_domain_is_ipi(domain)) {
		pr_warn("Trying to destroy a non IPI domain!\n");
		return -EINVAL;
	}

	if (WARN_ON(!cpumask_subset(dest, ipimask)))
		/*
		 * Must be destroying a subset of CPUs to which this IPI
		 * was set up to target
		 */
		return -EINVAL;

	if (irq_domain_is_ipi_per_cpu(domain)) {
		irq = irq + cpumask_first(dest) - data->common->ipi_offset;
		nr_irqs = cpumask_weight(dest);
	} else {
		nr_irqs = 1;
	}

	irq_domain_free_irqs(irq, nr_irqs);
	return 0;
}