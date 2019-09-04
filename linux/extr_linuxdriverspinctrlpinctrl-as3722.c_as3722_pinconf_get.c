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
typedef  int u16 ;
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
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int as3722_pinconf_get(struct pinctrl_dev *pctldev,
			unsigned pin, unsigned long *config)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	int arg = 0;
	u16 prop;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		prop = AS3722_GPIO_MODE_PULL_UP |
				AS3722_GPIO_MODE_PULL_DOWN;
		if (!(as_pci->gpio_control[pin].mode_prop & prop))
			arg = 1;
		prop = 0;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		prop = AS3722_GPIO_MODE_PULL_UP;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		prop = AS3722_GPIO_MODE_PULL_DOWN;
		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		prop = AS3722_GPIO_MODE_OPEN_DRAIN;
		break;

	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		prop = AS3722_GPIO_MODE_HIGH_IMPED;
		break;

	default:
		dev_err(as_pci->dev, "Properties not supported\n");
		return -ENOTSUPP;
	}

	if (as_pci->gpio_control[pin].mode_prop & prop)
		arg = 1;

	*config = pinconf_to_config_packed(param, (u16)arg);
	return 0;
}