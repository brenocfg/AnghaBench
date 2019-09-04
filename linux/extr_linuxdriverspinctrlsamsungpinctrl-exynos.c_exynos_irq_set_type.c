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
struct irq_data {unsigned int hwirq; } ;
struct irq_chip {int dummy; } ;
struct exynos_irq_chip {unsigned long eint_con; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EXYNOS_EINT_CON_LEN ; 
 unsigned int EXYNOS_EINT_CON_MASK ; 
 unsigned int EXYNOS_EINT_EDGE_BOTH ; 
 unsigned int EXYNOS_EINT_EDGE_FALLING ; 
 unsigned int EXYNOS_EINT_EDGE_RISING ; 
 unsigned int EXYNOS_EINT_LEVEL_HIGH ; 
 unsigned int EXYNOS_EINT_LEVEL_LOW ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct samsung_pin_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned int readl (scalar_t__) ; 
 struct exynos_irq_chip* to_exynos_irq_chip (struct irq_chip*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int exynos_irq_set_type(struct irq_data *irqd, unsigned int type)
{
	struct irq_chip *chip = irq_data_get_irq_chip(irqd);
	struct exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	struct samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	unsigned int shift = EXYNOS_EINT_CON_LEN * irqd->hwirq;
	unsigned int con, trig_type;
	unsigned long reg_con = our_chip->eint_con + bank->eint_offset;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		trig_type = EXYNOS_EINT_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		trig_type = EXYNOS_EINT_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		trig_type = EXYNOS_EINT_EDGE_BOTH;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		trig_type = EXYNOS_EINT_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		trig_type = EXYNOS_EINT_LEVEL_LOW;
		break;
	default:
		pr_err("unsupported external interrupt type\n");
		return -EINVAL;
	}

	if (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(irqd, handle_edge_irq);
	else
		irq_set_handler_locked(irqd, handle_level_irq);

	con = readl(bank->eint_base + reg_con);
	con &= ~(EXYNOS_EINT_CON_MASK << shift);
	con |= trig_type << shift;
	writel(con, bank->eint_base + reg_con);

	return 0;
}