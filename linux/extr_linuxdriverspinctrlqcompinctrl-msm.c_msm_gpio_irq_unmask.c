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
typedef  int /*<<< orphan*/  u32 ;
struct msm_pingroup {scalar_t__ intr_cfg_reg; int /*<<< orphan*/  intr_enable_bit; int /*<<< orphan*/  intr_raw_status_bit; } ;
struct msm_pinctrl {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled_irqs; scalar_t__ regs; TYPE_1__* soc; } ;
struct irq_data {size_t hwirq; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct msm_pingroup* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct msm_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void msm_gpio_irq_unmask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct msm_pinctrl *pctrl = gpiochip_get_data(gc);
	const struct msm_pingroup *g;
	unsigned long flags;
	u32 val;

	g = &pctrl->soc->groups[d->hwirq];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = readl(pctrl->regs + g->intr_cfg_reg);
	val |= BIT(g->intr_raw_status_bit);
	val |= BIT(g->intr_enable_bit);
	writel(val, pctrl->regs + g->intr_cfg_reg);

	set_bit(d->hwirq, pctrl->enabled_irqs);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
}