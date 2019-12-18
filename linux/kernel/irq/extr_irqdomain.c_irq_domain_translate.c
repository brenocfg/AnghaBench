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
struct irq_fwspec {int /*<<< orphan*/ * param; int /*<<< orphan*/  param_count; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {int (* translate ) (struct irq_domain*,struct irq_fwspec*,int /*<<< orphan*/ *,unsigned int*) ;int (* xlate ) (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ;} ;

/* Variables and functions */
 int stub1 (struct irq_domain*,struct irq_fwspec*,int /*<<< orphan*/ *,unsigned int*) ; 
 int stub2 (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irq_domain_translate(struct irq_domain *d,
				struct irq_fwspec *fwspec,
				irq_hw_number_t *hwirq, unsigned int *type)
{
#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY
	if (d->ops->translate)
		return d->ops->translate(d, fwspec, hwirq, type);
#endif
	if (d->ops->xlate)
		return d->ops->xlate(d, to_of_node(fwspec->fwnode),
				     fwspec->param, fwspec->param_count,
				     hwirq, type);

	/* If domain has no translation, then we assume interrupt line */
	*hwirq = fwspec->param[0];
	return 0;
}