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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  LPC18XX_SCU_USB1_EPD ; 
 int /*<<< orphan*/  LPC18XX_SCU_USB1_EPWR ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_LOW_POWER_MODE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int lpc18xx_pconf_set_usb1(struct pinctrl_dev *pctldev,
				  enum pin_config_param param,
				  u32 param_val, u32 *reg)
{
	switch (param) {
	case PIN_CONFIG_LOW_POWER_MODE:
		if (param_val)
			*reg &= ~LPC18XX_SCU_USB1_EPWR;
		else
			*reg |= LPC18XX_SCU_USB1_EPWR;
		break;

	case PIN_CONFIG_BIAS_DISABLE:
		*reg &= ~LPC18XX_SCU_USB1_EPD;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		*reg |= LPC18XX_SCU_USB1_EPD;
		break;

	default:
		dev_err(pctldev->dev, "Property not supported\n");
		return -ENOTSUPP;
	}

	return 0;
}