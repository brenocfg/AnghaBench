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
struct samsung_pin_bank {int /*<<< orphan*/  slock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct samsung_pin_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int samsung_gpio_set_direction (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  samsung_gpio_set_value (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int samsung_gpio_direction_output(struct gpio_chip *gc, unsigned offset,
							int value)
{
	struct samsung_pin_bank *bank = gpiochip_get_data(gc);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&bank->slock, flags);
	samsung_gpio_set_value(gc, offset, value);
	ret = samsung_gpio_set_direction(gc, offset, false);
	spin_unlock_irqrestore(&bank->slock, flags);

	return ret;
}