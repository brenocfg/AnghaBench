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
struct irq_domain_ops {int dummy; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SPARSE_IRQ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct irq_domain* __irq_domain_add (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,struct irq_domain_ops const*,void*) ; 
 int irq_alloc_descs (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_associate_many (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_nid (struct device_node*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

struct irq_domain *irq_domain_add_simple(struct device_node *of_node,
					 unsigned int size,
					 unsigned int first_irq,
					 const struct irq_domain_ops *ops,
					 void *host_data)
{
	struct irq_domain *domain;

	domain = __irq_domain_add(of_node_to_fwnode(of_node), size, size, 0, ops, host_data);
	if (!domain)
		return NULL;

	if (first_irq > 0) {
		if (IS_ENABLED(CONFIG_SPARSE_IRQ)) {
			/* attempt to allocated irq_descs */
			int rc = irq_alloc_descs(first_irq, first_irq, size,
						 of_node_to_nid(of_node));
			if (rc < 0)
				pr_info("Cannot allocate irq_descs @ IRQ%d, assuming pre-allocated\n",
					first_irq);
		}
		irq_domain_associate_many(domain, first_irq, 0, size);
	}

	return domain;
}