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
struct samsung_pinctrl_drv_data {scalar_t__ virt_base; } ;
struct samsung_pin_bank {struct samsung_pinctrl_drv_data* drvdata; } ;
struct irq_data {unsigned long hwirq; } ;

/* Variables and functions */
 scalar_t__ EINTPEND_REG ; 
 struct samsung_pin_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void s3c2412_eint0_3_ack(struct irq_data *data)
{
	struct samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	struct samsung_pinctrl_drv_data *d = bank->drvdata;

	unsigned long bitval = 1UL << data->hwirq;
	writel(bitval, d->virt_base + EINTPEND_REG);
}