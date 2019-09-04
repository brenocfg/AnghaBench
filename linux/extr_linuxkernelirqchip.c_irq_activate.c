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
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int irq_domain_activate_irq (struct irq_data*,int) ; 
 int /*<<< orphan*/  irqd_affinity_is_managed (struct irq_data*) ; 

int irq_activate(struct irq_desc *desc)
{
	struct irq_data *d = irq_desc_get_irq_data(desc);

	if (!irqd_affinity_is_managed(d))
		return irq_domain_activate_irq(d, false);
	return 0;
}