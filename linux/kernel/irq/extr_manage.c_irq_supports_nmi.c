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
struct irq_desc {int dummy; } ;
struct irq_data {TYPE_1__* chip; scalar_t__ parent_data; } ;
struct TYPE_2__ {int flags; scalar_t__ irq_bus_sync_unlock; scalar_t__ irq_bus_lock; } ;

/* Variables and functions */
 int IRQCHIP_SUPPORTS_NMI ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 

__attribute__((used)) static bool irq_supports_nmi(struct irq_desc *desc)
{
	struct irq_data *d = irq_desc_get_irq_data(desc);

#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY
	/* Only IRQs directly managed by the root irqchip can be set as NMI */
	if (d->parent_data)
		return false;
#endif
	/* Don't support NMIs for chips behind a slow bus */
	if (d->chip->irq_bus_lock || d->chip->irq_bus_sync_unlock)
		return false;

	return d->chip->flags & IRQCHIP_SUPPORTS_NMI;
}