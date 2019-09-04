#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rockchip_pinctrl {struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int nr_banks; struct rockchip_pin_bank* pin_banks; } ;
struct rockchip_pin_bank {int /*<<< orphan*/  clk; int /*<<< orphan*/  domain; int /*<<< orphan*/  irq; int /*<<< orphan*/  nr_pins; scalar_t__ reg_base; int /*<<< orphan*/  name; int /*<<< orphan*/  of_node; int /*<<< orphan*/  valid; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct irq_chip_generic {int /*<<< orphan*/  wake_enabled; TYPE_3__* chip_types; struct rockchip_pin_bank* private; scalar_t__ reg_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_resume; int /*<<< orphan*/  irq_suspend; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct TYPE_4__ {int /*<<< orphan*/  ack; scalar_t__ mask; } ;
struct TYPE_6__ {TYPE_2__ chip; TYPE_1__ regs; } ;

/* Variables and functions */
 scalar_t__ GPIO_INTEN ; 
 scalar_t__ GPIO_INTMASK ; 
 int /*<<< orphan*/  GPIO_PORTS_EOI ; 
 int /*<<< orphan*/  IRQ_GC_INIT_MASK_CACHE ; 
 int /*<<< orphan*/  IRQ_MSK (int /*<<< orphan*/ ) ; 
 unsigned int IRQ_NOAUTOEN ; 
 unsigned int IRQ_NOPROBE ; 
 unsigned int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_alloc_domain_generic_chips (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_gc_ack_set_bit ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit ; 
 int /*<<< orphan*/  irq_gc_set_wake ; 
 int /*<<< orphan*/  irq_generic_chip_ops ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rockchip_pin_bank*) ; 
 int /*<<< orphan*/  rockchip_irq_demux ; 
 int /*<<< orphan*/  rockchip_irq_disable ; 
 int /*<<< orphan*/  rockchip_irq_enable ; 
 int /*<<< orphan*/  rockchip_irq_resume ; 
 int /*<<< orphan*/  rockchip_irq_set_type ; 
 int /*<<< orphan*/  rockchip_irq_suspend ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int rockchip_interrupts_register(struct platform_device *pdev,
						struct rockchip_pinctrl *info)
{
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct rockchip_pin_bank *bank = ctrl->pin_banks;
	unsigned int clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	struct irq_chip_generic *gc;
	int ret;
	int i, j;

	for (i = 0; i < ctrl->nr_banks; ++i, ++bank) {
		if (!bank->valid) {
			dev_warn(&pdev->dev, "bank %s is not valid\n",
				 bank->name);
			continue;
		}

		ret = clk_enable(bank->clk);
		if (ret) {
			dev_err(&pdev->dev, "failed to enable clock for bank %s\n",
				bank->name);
			continue;
		}

		bank->domain = irq_domain_add_linear(bank->of_node, 32,
						&irq_generic_chip_ops, NULL);
		if (!bank->domain) {
			dev_warn(&pdev->dev, "could not initialize irq domain for bank %s\n",
				 bank->name);
			clk_disable(bank->clk);
			continue;
		}

		ret = irq_alloc_domain_generic_chips(bank->domain, 32, 1,
					 "rockchip_gpio_irq", handle_level_irq,
					 clr, 0, IRQ_GC_INIT_MASK_CACHE);
		if (ret) {
			dev_err(&pdev->dev, "could not alloc generic chips for bank %s\n",
				bank->name);
			irq_domain_remove(bank->domain);
			clk_disable(bank->clk);
			continue;
		}

		/*
		 * Linux assumes that all interrupts start out disabled/masked.
		 * Our driver only uses the concept of masked and always keeps
		 * things enabled, so for us that's all masked and all enabled.
		 */
		writel_relaxed(0xffffffff, bank->reg_base + GPIO_INTMASK);
		writel_relaxed(0xffffffff, bank->reg_base + GPIO_INTEN);

		gc = irq_get_domain_generic_chip(bank->domain, 0);
		gc->reg_base = bank->reg_base;
		gc->private = bank;
		gc->chip_types[0].regs.mask = GPIO_INTMASK;
		gc->chip_types[0].regs.ack = GPIO_PORTS_EOI;
		gc->chip_types[0].chip.irq_ack = irq_gc_ack_set_bit;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_set_bit;
		gc->chip_types[0].chip.irq_unmask = irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_enable = rockchip_irq_enable;
		gc->chip_types[0].chip.irq_disable = rockchip_irq_disable;
		gc->chip_types[0].chip.irq_set_wake = irq_gc_set_wake;
		gc->chip_types[0].chip.irq_suspend = rockchip_irq_suspend;
		gc->chip_types[0].chip.irq_resume = rockchip_irq_resume;
		gc->chip_types[0].chip.irq_set_type = rockchip_irq_set_type;
		gc->wake_enabled = IRQ_MSK(bank->nr_pins);

		irq_set_chained_handler_and_data(bank->irq,
						 rockchip_irq_demux, bank);

		/* map the gpio irqs here, when the clock is still running */
		for (j = 0 ; j < 32 ; j++)
			irq_create_mapping(bank->domain, j);

		clk_disable(bank->clk);
	}

	return 0;
}