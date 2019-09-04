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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_pinctrl {int /*<<< orphan*/  eint; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ PIN_CONFIG_INPUT_DEBOUNCE ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int mtk_eint_set_debounce (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 scalar_t__ pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int mtk_gpio_set_config(struct gpio_chip *chip, unsigned int offset,
			       unsigned long config)
{
	struct mtk_pinctrl *hw = gpiochip_get_data(chip);
	unsigned long eint_n;
	u32 debounce;

	if (!hw->eint ||
	    pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		return -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	eint_n = offset;

	return mtk_eint_set_debounce(hw->eint, eint_n, debounce);
}