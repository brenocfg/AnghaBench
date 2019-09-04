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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_controller {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_to_gpio_chip (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_gpio_irq_bus_lock(struct irq_data *d)
{
	struct gpio_chip *chip = irq_data_to_gpio_chip(d);
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	mutex_lock(&ggc->irq_lock);
}