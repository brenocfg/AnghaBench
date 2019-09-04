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
struct irq_data {struct irq_domain* domain; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_disassociate (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_free_irqs (unsigned int,int) ; 
 scalar_t__ irq_domain_is_hierarchy (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_free_desc (unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 

void irq_dispose_mapping(unsigned int virq)
{
	struct irq_data *irq_data = irq_get_irq_data(virq);
	struct irq_domain *domain;

	if (!virq || !irq_data)
		return;

	domain = irq_data->domain;
	if (WARN_ON(domain == NULL))
		return;

	if (irq_domain_is_hierarchy(domain)) {
		irq_domain_free_irqs(virq, 1);
	} else {
		irq_domain_disassociate(domain, virq);
		irq_free_desc(virq);
	}
}