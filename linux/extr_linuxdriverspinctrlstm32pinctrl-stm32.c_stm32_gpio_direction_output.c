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
struct stm32_gpio_bank {int dummy; } ;
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __stm32_gpio_set (struct stm32_gpio_bank*,unsigned int,int) ; 
 struct stm32_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinctrl_gpio_direction_output (unsigned int) ; 

__attribute__((used)) static int stm32_gpio_direction_output(struct gpio_chip *chip,
	unsigned offset, int value)
{
	struct stm32_gpio_bank *bank = gpiochip_get_data(chip);

	__stm32_gpio_set(bank, offset, value);
	pinctrl_gpio_direction_output(chip->base + offset);

	return 0;
}