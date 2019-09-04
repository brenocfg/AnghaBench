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
struct gpio_chip {scalar_t__ base; } ;
struct atlas7_gpio_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __atlas7_gpio_irq_mask (struct atlas7_gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  __atlas7_gpio_set_input (struct atlas7_gpio_chip*,unsigned int) ; 
 int __atlas7_gpio_to_pin (struct atlas7_gpio_chip*,unsigned int) ; 
 struct atlas7_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ pinctrl_gpio_request (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atlas7_gpio_request(struct gpio_chip *chip,
				unsigned int gpio)
{
	struct atlas7_gpio_chip *a7gc = gpiochip_get_data(chip);
	int ret;
	unsigned long flags;

	ret = __atlas7_gpio_to_pin(a7gc, gpio);
	if (ret < 0)
		return ret;

	if (pinctrl_gpio_request(chip->base + gpio))
		return -ENODEV;

	raw_spin_lock_irqsave(&a7gc->lock, flags);

	/*
	 * default status:
	 * set direction as input and mask irq
	 */
	__atlas7_gpio_set_input(a7gc, gpio);
	__atlas7_gpio_irq_mask(a7gc, gpio);

	raw_spin_unlock_irqrestore(&a7gc->lock, flags);

	return 0;
}