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
struct nmk_gpio_chip {int real_wake; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  __nmk_gpio_irq_modify (struct nmk_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __nmk_gpio_set_wake (struct nmk_gpio_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  nmk_gpio_slpm_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nmk_gpio_irq_maskunmask(struct irq_data *d, bool enable)
{
	struct nmk_gpio_chip *nmk_chip;
	unsigned long flags;

	nmk_chip = irq_data_get_irq_chip_data(d);
	if (!nmk_chip)
		return -EINVAL;

	clk_enable(nmk_chip->clk);
	spin_lock_irqsave(&nmk_gpio_slpm_lock, flags);
	spin_lock(&nmk_chip->lock);

	__nmk_gpio_irq_modify(nmk_chip, d->hwirq, NORMAL, enable);

	if (!(nmk_chip->real_wake & BIT(d->hwirq)))
		__nmk_gpio_set_wake(nmk_chip, d->hwirq, enable);

	spin_unlock(&nmk_chip->lock);
	spin_unlock_irqrestore(&nmk_gpio_slpm_lock, flags);
	clk_disable(nmk_chip->clk);

	return 0;
}