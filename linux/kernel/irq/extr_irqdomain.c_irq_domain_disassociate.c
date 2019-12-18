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
struct irq_domain {int /*<<< orphan*/  mapcount; TYPE_1__* ops; } ;
struct irq_data {scalar_t__ hwirq; struct irq_domain* domain; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap ) (struct irq_domain*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 scalar_t__ WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_clear_mapping (struct irq_domain*,scalar_t__) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  synchronize_irq (unsigned int) ; 

void irq_domain_disassociate(struct irq_domain *domain, unsigned int irq)
{
	struct irq_data *irq_data = irq_get_irq_data(irq);
	irq_hw_number_t hwirq;

	if (WARN(!irq_data || irq_data->domain != domain,
		 "virq%i doesn't exist; cannot disassociate\n", irq))
		return;

	hwirq = irq_data->hwirq;
	irq_set_status_flags(irq, IRQ_NOREQUEST);

	/* remove chip and handler */
	irq_set_chip_and_handler(irq, NULL, NULL);

	/* Make sure it's completed */
	synchronize_irq(irq);

	/* Tell the PIC about it */
	if (domain->ops->unmap)
		domain->ops->unmap(domain, irq);
	smp_mb();

	irq_data->domain = NULL;
	irq_data->hwirq = 0;
	domain->mapcount--;

	/* Clear reverse map for this hwirq */
	irq_domain_clear_mapping(domain, hwirq);
}