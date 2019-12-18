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
struct irq_domain_chip_generic {unsigned int irqs_per_chip; int num_chips; struct irq_chip_generic** gc; } ;
struct irq_domain {struct irq_domain_chip_generic* gc; } ;
struct irq_chip_generic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct irq_chip_generic* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct irq_chip_generic *
__irq_get_domain_generic_chip(struct irq_domain *d, unsigned int hw_irq)
{
	struct irq_domain_chip_generic *dgc = d->gc;
	int idx;

	if (!dgc)
		return ERR_PTR(-ENODEV);
	idx = hw_irq / dgc->irqs_per_chip;
	if (idx >= dgc->num_chips)
		return ERR_PTR(-EINVAL);
	return dgc->gc[idx];
}