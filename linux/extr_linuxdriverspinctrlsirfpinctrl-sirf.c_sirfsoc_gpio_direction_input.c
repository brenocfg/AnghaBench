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
struct sirfsoc_gpio_chip {int dummy; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  sirfsoc_gpio_set_input (struct sirfsoc_gpio_chip*,unsigned int) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,unsigned int) ; 
 int sirfsoc_gpio_to_bankoff (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sirfsoc_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	struct sirfsoc_gpio_chip *sgpio = gpiochip_get_data(chip);
	struct sirfsoc_gpio_bank *bank = sirfsoc_gpio_to_bank(sgpio, gpio);
	int idx = sirfsoc_gpio_to_bankoff(gpio);
	unsigned long flags;
	unsigned offset;

	offset = SIRFSOC_GPIO_CTRL(bank->id, idx);

	spin_lock_irqsave(&bank->lock, flags);

	sirfsoc_gpio_set_input(sgpio, offset);

	spin_unlock_irqrestore(&bank->lock, flags);

	return 0;
}