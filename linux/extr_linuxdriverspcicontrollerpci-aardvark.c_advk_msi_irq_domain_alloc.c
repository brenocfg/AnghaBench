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
struct irq_domain {struct advk_pcie* host_data; } ;
struct advk_pcie {int /*<<< orphan*/  msi_bottom_irq_chip; int /*<<< orphan*/  msi_used_lock; int /*<<< orphan*/  msi_used; } ;

/* Variables and functions */
 int ENOSPC ; 
 int MSI_IRQ_NUM ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct advk_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int advk_msi_irq_domain_alloc(struct irq_domain *domain,
				     unsigned int virq,
				     unsigned int nr_irqs, void *args)
{
	struct advk_pcie *pcie = domain->host_data;
	int hwirq, i;

	mutex_lock(&pcie->msi_used_lock);
	hwirq = bitmap_find_next_zero_area(pcie->msi_used, MSI_IRQ_NUM,
					   0, nr_irqs, 0);
	if (hwirq >= MSI_IRQ_NUM) {
		mutex_unlock(&pcie->msi_used_lock);
		return -ENOSPC;
	}

	bitmap_set(pcie->msi_used, hwirq, nr_irqs);
	mutex_unlock(&pcie->msi_used_lock);

	for (i = 0; i < nr_irqs; i++)
		irq_domain_set_info(domain, virq + i, hwirq + i,
				    &pcie->msi_bottom_irq_chip,
				    domain->host_data, handle_simple_irq,
				    NULL, NULL);

	return hwirq;
}