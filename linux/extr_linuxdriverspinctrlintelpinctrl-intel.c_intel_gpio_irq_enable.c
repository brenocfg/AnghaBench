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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int dummy; } ;
struct intel_pinctrl {int /*<<< orphan*/  lock; } ;
struct intel_padgroup {unsigned int reg_num; } ;
struct intel_community {unsigned int is_offset; scalar_t__ ie_offset; scalar_t__ regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct intel_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int intel_gpio_to_pin (struct intel_pinctrl*,int /*<<< orphan*/ ,struct intel_community const**,struct intel_padgroup const**) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 unsigned int padgroup_offset (struct intel_padgroup const*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_gpio_irq_enable(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct intel_pinctrl *pctrl = gpiochip_get_data(gc);
	const struct intel_community *community;
	const struct intel_padgroup *padgrp;
	int pin;

	pin = intel_gpio_to_pin(pctrl, irqd_to_hwirq(d), &community, &padgrp);
	if (pin >= 0) {
		unsigned gpp, gpp_offset, is_offset;
		unsigned long flags;
		u32 value;

		gpp = padgrp->reg_num;
		gpp_offset = padgroup_offset(padgrp, pin);
		is_offset = community->is_offset + gpp * 4;

		raw_spin_lock_irqsave(&pctrl->lock, flags);
		/* Clear interrupt status first to avoid unexpected interrupt */
		writel(BIT(gpp_offset), community->regs + is_offset);

		value = readl(community->regs + community->ie_offset + gpp * 4);
		value |= BIT(gpp_offset);
		writel(value, community->regs + community->ie_offset + gpp * 4);
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	}
}