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
struct s3c24xx_eint_data {int /*<<< orphan*/ * domains; } ;
struct irq_desc {int dummy; } ;
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct s3c24xx_eint_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void s3c2410_demux_eint0_3(struct irq_desc *desc)
{
	struct irq_data *data = irq_desc_get_irq_data(desc);
	struct s3c24xx_eint_data *eint_data = irq_desc_get_handler_data(desc);
	unsigned int virq;

	/* the first 4 eints have a simple 1 to 1 mapping */
	virq = irq_linear_revmap(eint_data->domains[data->hwirq], data->hwirq);
	/* Something must be really wrong if an unmapped EINT is unmasked */
	BUG_ON(!virq);

	generic_handle_irq(virq);
}