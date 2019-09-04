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
 int EINVAL ; 
 int IRQ_CFG_IRQ_MASK ; 
 int IRQ_EDGE_BOTH ; 
 int IRQ_EDGE_FALLING ; 
 int IRQ_EDGE_RISING ; 
 int IRQ_LEVEL_HIGH ; 
 int IRQ_LEVEL_LOW ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_LEVEL_MASK ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 struct sunxi_pinctrl* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_chip_handler_name_locked (struct irq_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int) ; 
 int sunxi_irq_cfg_offset (int /*<<< orphan*/ ) ; 
 int sunxi_irq_cfg_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_pinctrl_edge_irq_chip ; 
 int /*<<< orphan*/  sunxi_pinctrl_level_irq_chip ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int sunxi_pinctrl_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 reg = sunxi_irq_cfg_reg(pctl->desc, d->hwirq);
	u8 index = sunxi_irq_cfg_offset(d->hwirq);
	unsigned long flags;
	u32 regval;
	u8 mode;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		mode = IRQ_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		mode = IRQ_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		mode = IRQ_EDGE_BOTH;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		mode = IRQ_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		mode = IRQ_LEVEL_LOW;
		break;
	default:
		return -EINVAL;
	}

	raw_spin_lock_irqsave(&pctl->lock, flags);

	if (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_chip_handler_name_locked(d, &sunxi_pinctrl_level_irq_chip,
						 handle_fasteoi_irq, NULL);
	else
		irq_set_chip_handler_name_locked(d, &sunxi_pinctrl_edge_irq_chip,
						 handle_edge_irq, NULL);

	regval = readl(pctl->membase + reg);
	regval &= ~(IRQ_CFG_IRQ_MASK << index);
	writel(regval | (mode << index), pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);

	return 0;
}