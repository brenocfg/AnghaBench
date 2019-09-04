#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_6__ {int base; } ;
struct ns2_pin {TYPE_3__ pin_conf; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_5__ {TYPE_1__* pins; } ;
struct TYPE_4__ {struct ns2_pin* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH 130 
#define  PIN_CONFIG_INPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int ns2_pin_get_enable (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  ns2_pin_get_pull (struct pinctrl_dev*,unsigned int,int*,int*) ; 
 int ns2_pin_get_slew (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ *) ; 
 int ns2_pin_get_strength (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int ns2_pin_config_get(struct pinctrl_dev *pctldev, unsigned int pin,
			      unsigned long *config)
{
	struct ns2_pin *pin_data = pctldev->desc->pins[pin].drv_data;
	enum pin_config_param param = pinconf_to_config_param(*config);
	bool pull_up, pull_down;
	u16 arg = 0;
	int ret;

	if (pin_data->pin_conf.base == -1)
		return -ENOTSUPP;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_down);
		if ((pull_up == false) && (pull_down == false))
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_BIAS_PULL_UP:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_down);
		if (pull_up)
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_down);
		if (pull_down)
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_DRIVE_STRENGTH:
		ret = ns2_pin_get_strength(pctldev, pin, &arg);
		if (ret)
			return ret;
		*config = pinconf_to_config_packed(param, arg);
		return 0;

	case PIN_CONFIG_SLEW_RATE:
		ret = ns2_pin_get_slew(pctldev, pin, &arg);
		if (ret)
			return ret;
		*config = pinconf_to_config_packed(param, arg);
		return 0;

	case PIN_CONFIG_INPUT_ENABLE:
		ret = ns2_pin_get_enable(pctldev, pin);
		if (ret)
			return 0;
		else
			return -EINVAL;

	default:
		return -ENOTSUPP;
	}
}