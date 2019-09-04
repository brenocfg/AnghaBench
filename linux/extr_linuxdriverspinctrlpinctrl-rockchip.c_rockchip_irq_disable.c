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
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit (struct irq_data*) ; 

__attribute__((used)) static void rockchip_irq_disable(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct rockchip_pin_bank *bank = gc->private;

	irq_gc_mask_set_bit(d);
	clk_disable(bank->clk);
}