#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mtk_pinctrl {int /*<<< orphan*/  eint; TYPE_1__* devdata; } ;
struct TYPE_4__ {unsigned long eintnum; } ;
struct mtk_desc_pin {TYPE_2__ eint; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct mtk_desc_pin* pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 unsigned long NO_EINT_SUPPORT ; 
 scalar_t__ PIN_CONFIG_INPUT_DEBOUNCE ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int mtk_eint_set_debounce (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 scalar_t__ pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int mtk_gpio_set_config(struct gpio_chip *chip, unsigned offset,
			       unsigned long config)
{
	struct mtk_pinctrl *pctl = gpiochip_get_data(chip);
	const struct mtk_desc_pin *pin;
	unsigned long eint_n;
	u32 debounce;

	if (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		return -ENOTSUPP;

	pin = pctl->devdata->pins + offset;
	if (pin->eint.eintnum == NO_EINT_SUPPORT)
		return -EINVAL;

	debounce = pinconf_to_config_argument(config);
	eint_n = pin->eint.eintnum;

	return mtk_eint_set_debounce(pctl->eint, eint_n, debounce);
}