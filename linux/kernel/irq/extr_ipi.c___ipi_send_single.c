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
struct irq_data {unsigned int irq; TYPE_1__* common; int /*<<< orphan*/  domain; } ;
struct irq_chip {int /*<<< orphan*/  (* ipi_send_single ) (struct irq_data*,unsigned int) ;int /*<<< orphan*/  (* ipi_send_mask ) (struct irq_data*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {unsigned int ipi_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  ipi_send_verify (struct irq_chip*,struct irq_data*,int /*<<< orphan*/ *,unsigned int) ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 scalar_t__ irq_domain_is_ipi_per_cpu (int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct irq_data*,unsigned int) ; 

int __ipi_send_single(struct irq_desc *desc, unsigned int cpu)
{
	struct irq_data *data = irq_desc_get_irq_data(desc);
	struct irq_chip *chip = irq_data_get_irq_chip(data);

#ifdef DEBUG
	/*
	 * Minimise the overhead by omitting the checks for Linux SMP IPIs.
	 * Since the callers should be arch or core code which is generally
	 * trusted, only check for errors when debugging.
	 */
	if (WARN_ON_ONCE(ipi_send_verify(chip, data, NULL, cpu)))
		return -EINVAL;
#endif
	if (!chip->ipi_send_single) {
		chip->ipi_send_mask(data, cpumask_of(cpu));
		return 0;
	}

	/* FIXME: Store this information in irqdata flags */
	if (irq_domain_is_ipi_per_cpu(data->domain) &&
	    cpu != data->common->ipi_offset) {
		/* use the correct data for that cpu */
		unsigned irq = data->irq + cpu - data->common->ipi_offset;

		data = irq_get_irq_data(irq);
	}
	chip->ipi_send_single(data, cpu);
	return 0;
}