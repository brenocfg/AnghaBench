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
struct irq_domain {unsigned int revmap_direct_max_irq; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int irq_alloc_desc_from (int,int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_default_domain ; 
 scalar_t__ irq_domain_associate (struct irq_domain*,unsigned int,unsigned int) ; 
 struct device_node* irq_domain_get_of_node (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_free_desc (unsigned int) ; 
 int /*<<< orphan*/  of_node_to_nid (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

unsigned int irq_create_direct_mapping(struct irq_domain *domain)
{
	struct device_node *of_node;
	unsigned int virq;

	if (domain == NULL)
		domain = irq_default_domain;

	of_node = irq_domain_get_of_node(domain);
	virq = irq_alloc_desc_from(1, of_node_to_nid(of_node));
	if (!virq) {
		pr_debug("create_direct virq allocation failed\n");
		return 0;
	}
	if (virq >= domain->revmap_direct_max_irq) {
		pr_err("ERROR: no free irqs available below %i maximum\n",
			domain->revmap_direct_max_irq);
		irq_free_desc(virq);
		return 0;
	}
	pr_debug("create_direct obtained virq %d\n", virq);

	if (irq_domain_associate(domain, virq, virq)) {
		irq_free_desc(virq);
		return 0;
	}

	return virq;
}