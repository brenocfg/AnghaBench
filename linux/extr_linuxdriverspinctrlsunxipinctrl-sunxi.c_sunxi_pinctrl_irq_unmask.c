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
typedef  int u8 ;
typedef  int u32 ;
struct sunxi_pinctrl {int membase; int /*<<< orphan*/  lock; int /*<<< orphan*/  desc; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 struct sunxi_pinctrl* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int) ; 
 int sunxi_irq_ctrl_offset (int /*<<< orphan*/ ) ; 
 int sunxi_irq_ctrl_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void sunxi_pinctrl_irq_unmask(struct irq_data *d)
{
	struct sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 reg = sunxi_irq_ctrl_reg(pctl->desc, d->hwirq);
	u8 idx = sunxi_irq_ctrl_offset(d->hwirq);
	unsigned long flags;
	u32 val;

	raw_spin_lock_irqsave(&pctl->lock, flags);

	/* Unmask the IRQ */
	val = readl(pctl->membase + reg);
	writel(val | (1 << idx), pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);
}