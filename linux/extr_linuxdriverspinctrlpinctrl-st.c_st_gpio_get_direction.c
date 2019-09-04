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
struct st_pio_control {int dummy; } ;
struct st_gpio_bank {scalar_t__ base; struct st_pio_control pc; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_PIO_PC (int) ; 
 unsigned int ST_GPIO_DIRECTION_IN ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_OE (unsigned long) ; 
 struct st_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int st_pctl_get_pin_function (struct st_pio_control*,unsigned int) ; 
 int /*<<< orphan*/  st_pinconf_get_direction (struct st_pio_control*,unsigned int,unsigned long*) ; 

__attribute__((used)) static int st_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct st_gpio_bank *bank = gpiochip_get_data(chip);
	struct st_pio_control pc = bank->pc;
	unsigned long config;
	unsigned int direction = 0;
	unsigned int function;
	unsigned int value;
	int i = 0;

	/* Alternate function direction is handled by Pinctrl */
	function = st_pctl_get_pin_function(&pc, offset);
	if (function) {
		st_pinconf_get_direction(&pc, offset, &config);
		return !ST_PINCONF_UNPACK_OE(config);
	}

	/*
	 * GPIO direction is handled differently
	 * - See st_gpio_direction() above for an explanation
	 */
	for (i = 0; i <= 2; i++) {
		value = readl(bank->base + REG_PIO_PC(i));
		direction |= ((value >> offset) & 0x1) << i;
	}

	return (direction == ST_GPIO_DIRECTION_IN);
}