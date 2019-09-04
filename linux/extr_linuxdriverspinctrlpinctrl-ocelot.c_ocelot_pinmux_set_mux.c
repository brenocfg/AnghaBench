#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct ocelot_pinctrl {int /*<<< orphan*/  map; } ;
struct ocelot_pin_caps {int pin; } ;
struct TYPE_2__ {struct ocelot_pin_caps* drv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OCELOT_GPIO_ALT0 ; 
 int /*<<< orphan*/  OCELOT_GPIO_ALT1 ; 
 int ocelot_pin_function_idx (unsigned int,unsigned int) ; 
 TYPE_1__* ocelot_pins ; 
 struct ocelot_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocelot_pinmux_set_mux(struct pinctrl_dev *pctldev,
				 unsigned int selector, unsigned int group)
{
	struct ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	struct ocelot_pin_caps *pin = ocelot_pins[group].drv_data;
	int f;

	f = ocelot_pin_function_idx(group, selector);
	if (f < 0)
		return -EINVAL;

	/*
	 * f is encoded on two bits.
	 * bit 0 of f goes in BIT(pin) of ALT0, bit 1 of f goes in BIT(pin) of
	 * ALT1
	 * This is racy because both registers can't be updated at the same time
	 * but it doesn't matter much for now.
	 */
	regmap_update_bits(info->map, OCELOT_GPIO_ALT0, BIT(pin->pin),
			   f << pin->pin);
	regmap_update_bits(info->map, OCELOT_GPIO_ALT1, BIT(pin->pin),
			   f << (pin->pin - 1));

	return 0;
}