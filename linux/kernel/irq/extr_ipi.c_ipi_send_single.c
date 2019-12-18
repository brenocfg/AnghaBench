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
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int __ipi_send_single (struct irq_desc*,unsigned int) ; 
 int /*<<< orphan*/  ipi_send_verify (struct irq_chip*,struct irq_data*,int /*<<< orphan*/ *,unsigned int) ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

int ipi_send_single(unsigned int virq, unsigned int cpu)
{
	struct irq_desc *desc = irq_to_desc(virq);
	struct irq_data *data = desc ? irq_desc_get_irq_data(desc) : NULL;
	struct irq_chip *chip = data ? irq_data_get_irq_chip(data) : NULL;

	if (WARN_ON_ONCE(ipi_send_verify(chip, data, NULL, cpu)))
		return -EINVAL;

	return __ipi_send_single(desc, cpu);
}