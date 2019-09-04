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
struct pmic_gpio_state {int /*<<< orphan*/  ctrl; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_CONFIG_INPUT_ENABLE ; 
 struct pmic_gpio_state* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long pinconf_to_config_packed (int /*<<< orphan*/ ,int) ; 
 int pmic_gpio_config_set (int /*<<< orphan*/ ,unsigned int,unsigned long*,int) ; 

__attribute__((used)) static int pmic_gpio_direction_input(struct gpio_chip *chip, unsigned pin)
{
	struct pmic_gpio_state *state = gpiochip_get_data(chip);
	unsigned long config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABLE, 1);

	return pmic_gpio_config_set(state->ctrl, pin, &config, 1);
}