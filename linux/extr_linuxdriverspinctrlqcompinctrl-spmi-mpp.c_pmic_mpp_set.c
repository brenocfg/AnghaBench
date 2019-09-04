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
struct pmic_mpp_state {int /*<<< orphan*/  ctrl; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_CONFIG_OUTPUT ; 
 struct pmic_mpp_state* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long pinconf_to_config_packed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmic_mpp_config_set (int /*<<< orphan*/ ,unsigned int,unsigned long*,int) ; 

__attribute__((used)) static void pmic_mpp_set(struct gpio_chip *chip, unsigned pin, int value)
{
	struct pmic_mpp_state *state = gpiochip_get_data(chip);
	unsigned long config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, value);

	pmic_mpp_config_set(state->ctrl, pin, &config, 1);
}