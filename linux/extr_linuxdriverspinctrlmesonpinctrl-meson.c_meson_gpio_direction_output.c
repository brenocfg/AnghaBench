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
struct meson_pinctrl {int /*<<< orphan*/  reg_gpio; } ;
struct meson_bank {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  REG_DIR ; 
 int /*<<< orphan*/  REG_OUT ; 
 struct meson_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_gpio_direction_output(struct gpio_chip *chip, unsigned gpio,
				       int value)
{
	struct meson_pinctrl *pc = gpiochip_get_data(chip);
	unsigned int reg, bit;
	struct meson_bank *bank;
	int ret;

	ret = meson_get_bank(pc, gpio, &bank);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, gpio, REG_DIR, &reg, &bit);
	ret = regmap_update_bits(pc->reg_gpio, reg, BIT(bit), 0);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, gpio, REG_OUT, &reg, &bit);
	return regmap_update_bits(pc->reg_gpio, reg, BIT(bit),
				  value ? BIT(bit) : 0);
}