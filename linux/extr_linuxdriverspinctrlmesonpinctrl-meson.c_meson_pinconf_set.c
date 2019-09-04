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
struct pinctrl_dev {int dummy; } ;
struct meson_pinctrl {int /*<<< orphan*/  reg_pull; int /*<<< orphan*/  reg_pullen; int /*<<< orphan*/  dev; } ;
struct meson_bank {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 int /*<<< orphan*/  REG_PULL ; 
 int /*<<< orphan*/  REG_PULLEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_pinconf_set(struct pinctrl_dev *pcdev, unsigned int pin,
			     unsigned long *configs, unsigned num_configs)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	struct meson_bank *bank;
	enum pin_config_param param;
	unsigned int reg, bit;
	int i, ret;

	ret = meson_get_bank(pc, pin, &bank);
	if (ret)
		return ret;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
			dev_dbg(pc->dev, "pin %u: disable bias\n", pin);

			meson_calc_reg_and_bit(bank, pin, REG_PULLEN, &reg,
					       &bit);
			ret = regmap_update_bits(pc->reg_pullen, reg,
						 BIT(bit), 0);
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(pc->dev, "pin %u: enable pull-up\n", pin);

			meson_calc_reg_and_bit(bank, pin, REG_PULLEN,
					       &reg, &bit);
			ret = regmap_update_bits(pc->reg_pullen, reg,
						 BIT(bit), BIT(bit));
			if (ret)
				return ret;

			meson_calc_reg_and_bit(bank, pin, REG_PULL, &reg, &bit);
			ret = regmap_update_bits(pc->reg_pull, reg,
						 BIT(bit), BIT(bit));
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			dev_dbg(pc->dev, "pin %u: enable pull-down\n", pin);

			meson_calc_reg_and_bit(bank, pin, REG_PULLEN,
					       &reg, &bit);
			ret = regmap_update_bits(pc->reg_pullen, reg,
						 BIT(bit), BIT(bit));
			if (ret)
				return ret;

			meson_calc_reg_and_bit(bank, pin, REG_PULL, &reg, &bit);
			ret = regmap_update_bits(pc->reg_pull, reg,
						 BIT(bit), 0);
			if (ret)
				return ret;
			break;
		default:
			return -ENOTSUPP;
		}
	}

	return 0;
}