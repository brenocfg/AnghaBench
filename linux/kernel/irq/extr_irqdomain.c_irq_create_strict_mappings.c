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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int irq_alloc_descs (unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_associate_many (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct device_node* irq_domain_get_of_node (struct irq_domain*) ; 
 int /*<<< orphan*/  of_node_to_nid (struct device_node*) ; 
 scalar_t__ unlikely (int) ; 

int irq_create_strict_mappings(struct irq_domain *domain, unsigned int irq_base,
			       irq_hw_number_t hwirq_base, int count)
{
	struct device_node *of_node;
	int ret;

	of_node = irq_domain_get_of_node(domain);
	ret = irq_alloc_descs(irq_base, irq_base, count,
			      of_node_to_nid(of_node));
	if (unlikely(ret < 0))
		return ret;

	irq_domain_associate_many(domain, irq_base, hwirq_base, count);
	return 0;
}