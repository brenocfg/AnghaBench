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
struct st_gpio_bank {int dummy; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gpio_irq_handler (struct st_gpio_bank*) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct st_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 

__attribute__((used)) static void st_gpio_irq_handler(struct irq_desc *desc)
{
	/* interrupt dedicated per bank */
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct gpio_chip *gc = irq_desc_get_handler_data(desc);
	struct st_gpio_bank *bank = gpiochip_get_data(gc);

	chained_irq_enter(chip, desc);
	__gpio_irq_handler(bank);
	chained_irq_exit(chip, desc);
}