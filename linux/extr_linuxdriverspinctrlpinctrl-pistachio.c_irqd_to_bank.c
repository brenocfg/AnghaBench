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
struct pistachio_gpio_bank {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct pistachio_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static inline struct pistachio_gpio_bank *irqd_to_bank(struct irq_data *d)
{
	return gpiochip_get_data(irq_data_get_irq_chip_data(d));
}