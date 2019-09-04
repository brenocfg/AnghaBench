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
typedef  int /*<<< orphan*/  u16 ;
struct pinctrl_dev {int dummy; } ;
struct lpc18xx_scu_data {scalar_t__ base; } ;
struct lpc18xx_pin_caps {scalar_t__ type; scalar_t__ offset; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TYPE_I2C0 ; 
 scalar_t__ TYPE_USB1 ; 
 struct lpc18xx_pin_caps* lpc18xx_get_pin_caps (unsigned int) ; 
 int lpc18xx_pconf_get_i2c0 (int,int*,int /*<<< orphan*/ ,unsigned int) ; 
 int lpc18xx_pconf_get_pin (struct pinctrl_dev*,int,int*,int /*<<< orphan*/ ,unsigned int,struct lpc18xx_pin_caps*) ; 
 int lpc18xx_pconf_get_usb1 (int,int*,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct lpc18xx_scu_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int lpc18xx_pconf_get(struct pinctrl_dev *pctldev, unsigned pin,
			     unsigned long *config)
{
	struct lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	struct lpc18xx_pin_caps *pin_cap;
	int ret, arg = 0;
	u32 reg;

	pin_cap = lpc18xx_get_pin_caps(pin);
	if (!pin_cap)
		return -EINVAL;

	reg = readl(scu->base + pin_cap->offset);

	if (pin_cap->type == TYPE_I2C0)
		ret = lpc18xx_pconf_get_i2c0(param, &arg, reg, pin);
	else if (pin_cap->type == TYPE_USB1)
		ret = lpc18xx_pconf_get_usb1(param, &arg, reg);
	else
		ret = lpc18xx_pconf_get_pin(pctldev, param, &arg, reg, pin, pin_cap);

	if (ret < 0)
		return ret;

	*config = pinconf_to_config_packed(param, (u16)arg);

	return 0;
}