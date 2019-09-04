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
struct as3722_pctrl_info {TYPE_1__* gpio_control; int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int mode_prop; } ;

/* Variables and functions */
 int AS3722_GPIO_MODE_HIGH_IMPED ; 
 int AS3722_GPIO_MODE_OPEN_DRAIN ; 
 int AS3722_GPIO_MODE_PULL_DOWN ; 
 int AS3722_GPIO_MODE_PULL_UP ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_PIN_DEFAULT 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int as3722_pinconf_set(struct pinctrl_dev *pctldev,
			unsigned pin, unsigned long *configs,
			unsigned num_configs)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	int mode_prop;
	int i;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		mode_prop = as_pci->gpio_control[pin].mode_prop;

		switch (param) {
		case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
			break;

		case PIN_CONFIG_BIAS_DISABLE:
			mode_prop &= ~(AS3722_GPIO_MODE_PULL_UP |
					AS3722_GPIO_MODE_PULL_DOWN);
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			mode_prop |= AS3722_GPIO_MODE_PULL_UP;
			break;

		case PIN_CONFIG_BIAS_PULL_DOWN:
			mode_prop |= AS3722_GPIO_MODE_PULL_DOWN;
			break;

		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			mode_prop |= AS3722_GPIO_MODE_HIGH_IMPED;
			break;

		case PIN_CONFIG_DRIVE_OPEN_DRAIN:
			mode_prop |= AS3722_GPIO_MODE_OPEN_DRAIN;
			break;

		default:
			dev_err(as_pci->dev, "Properties not supported\n");
			return -ENOTSUPP;
		}

		as_pci->gpio_control[pin].mode_prop = mode_prop;
	}
	return 0;
}