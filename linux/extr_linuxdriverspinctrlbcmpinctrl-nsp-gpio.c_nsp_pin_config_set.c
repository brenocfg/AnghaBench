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
struct pinctrl_dev {int dummy; } ;
struct nsp_gpio {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int nsp_gpio_set_pull (struct nsp_gpio*,unsigned int,int,int) ; 
 int nsp_gpio_set_slew (struct nsp_gpio*,unsigned int,int /*<<< orphan*/ ) ; 
 int nsp_gpio_set_strength (struct nsp_gpio*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int nsp_pin_to_gpio (unsigned int) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct nsp_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int nsp_pin_config_set(struct pinctrl_dev *pctldev, unsigned pin,
			      unsigned long *configs, unsigned num_configs)
{
	struct nsp_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	u32 arg;
	unsigned int i, gpio;
	int ret = -ENOTSUPP;

	gpio = nsp_pin_to_gpio(pin);
	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
			ret = nsp_gpio_set_pull(chip, gpio, false, false);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_BIAS_PULL_UP:
			ret = nsp_gpio_set_pull(chip, gpio, true, false);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_BIAS_PULL_DOWN:
			ret = nsp_gpio_set_pull(chip, gpio, false, true);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_DRIVE_STRENGTH:
			ret = nsp_gpio_set_strength(chip, gpio, arg);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_SLEW_RATE:
			ret = nsp_gpio_set_slew(chip, gpio, arg);
			if (ret < 0)
				goto out;
			break;

		default:
			dev_err(chip->dev, "invalid configuration\n");
			return -ENOTSUPP;
		}
	}

out:
	return ret;
}