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
struct rockchip_pin_bank {int /*<<< orphan*/  clk; } ;
struct irq_data {int dummy; } ;
struct irq_chip_generic {struct rockchip_pin_bank* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit (struct irq_data*) ; 

__attribute__((used)) static void rockchip_irq_enable(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct rockchip_pin_bank *bank = gc->private;

	clk_enable(bank->clk);
	irq_gc_mask_clr_bit(d);
}