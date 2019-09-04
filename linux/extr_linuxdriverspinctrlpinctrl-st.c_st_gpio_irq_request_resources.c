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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int gpiochip_lock_as_irq (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  st_gpio_direction_input (struct gpio_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_gpio_irq_request_resources(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);

	st_gpio_direction_input(gc, d->hwirq);

	return gpiochip_lock_as_irq(gc, d->hwirq);
}