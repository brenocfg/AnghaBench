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
struct samsung_pin_bank {unsigned long eint_offset; scalar_t__ eint_base; } ;
struct irq_data {int hwirq; } ;
struct irq_chip {int dummy; } ;
struct exynos_irq_chip {unsigned long eint_pend; } ;

/* Variables and functions */
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct samsung_pin_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct exynos_irq_chip* to_exynos_irq_chip (struct irq_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos_irq_ack(struct irq_data *irqd)
{
	struct irq_chip *chip = irq_data_get_irq_chip(irqd);
	struct exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	struct samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	unsigned long reg_pend = our_chip->eint_pend + bank->eint_offset;

	writel(1 << irqd->hwirq, bank->eint_base + reg_pend);
}