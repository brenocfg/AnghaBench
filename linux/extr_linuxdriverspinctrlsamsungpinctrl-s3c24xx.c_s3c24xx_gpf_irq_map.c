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
struct samsung_pin_bank {int eint_mask; int eint_offset; } ;
struct s3c24xx_eint_domain_data {scalar_t__ eint0_3_parent_only; struct samsung_pin_bank* bank; } ;
struct irq_domain {struct s3c24xx_eint_domain_data* host_data; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct samsung_pin_bank*) ; 
 int /*<<< orphan*/  s3c2410_eint0_3_chip ; 
 int /*<<< orphan*/  s3c2412_eint0_3_chip ; 
 int /*<<< orphan*/  s3c24xx_eint_chip ; 

__attribute__((used)) static int s3c24xx_gpf_irq_map(struct irq_domain *h, unsigned int virq,
					irq_hw_number_t hw)
{
	struct s3c24xx_eint_domain_data *ddata = h->host_data;
	struct samsung_pin_bank *bank = ddata->bank;

	if (!(bank->eint_mask & (1 << (bank->eint_offset + hw))))
		return -EINVAL;

	if (hw <= 3) {
		if (ddata->eint0_3_parent_only)
			irq_set_chip_and_handler(virq, &s3c2410_eint0_3_chip,
						 handle_edge_irq);
		else
			irq_set_chip_and_handler(virq, &s3c2412_eint0_3_chip,
						 handle_edge_irq);
	} else {
		irq_set_chip_and_handler(virq, &s3c24xx_eint_chip,
					 handle_edge_irq);
	}
	irq_set_chip_data(virq, bank);
	return 0;
}