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
typedef  int u32 ;
struct pistachio_pinctrl {int /*<<< orphan*/  dev; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PADS_DRIVE_STRENGTH_12MA 138 
#define  PADS_DRIVE_STRENGTH_2MA 137 
#define  PADS_DRIVE_STRENGTH_4MA 136 
#define  PADS_DRIVE_STRENGTH_8MA 135 
 int PADS_DRIVE_STRENGTH_MASK ; 
 int /*<<< orphan*/  PADS_DRIVE_STRENGTH_REG (unsigned int) ; 
 int PADS_DRIVE_STRENGTH_SHIFT (unsigned int) ; 
 int PADS_PU_PD_BUS ; 
 int PADS_PU_PD_DOWN ; 
 int PADS_PU_PD_HIGHZ ; 
 int PADS_PU_PD_MASK ; 
 int /*<<< orphan*/  PADS_PU_PD_REG (unsigned int) ; 
 int PADS_PU_PD_SHIFT (unsigned int) ; 
 int PADS_PU_PD_UP ; 
 int PADS_SCHMITT_EN_BIT (unsigned int) ; 
 int /*<<< orphan*/  PADS_SCHMITT_EN_REG (unsigned int) ; 
 int PADS_SLEW_RATE_BIT (unsigned int) ; 
 int /*<<< orphan*/  PADS_SLEW_RATE_REG (unsigned int) ; 
#define  PIN_CONFIG_BIAS_BUS_HOLD 134 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int pctl_readl (struct pistachio_pinctrl*,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct pistachio_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pistachio_pinconf_get(struct pinctrl_dev *pctldev, unsigned pin,
				 unsigned long *config)
{
	struct pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u32 val, arg;

	switch (param) {
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		val = pctl_readl(pctl, PADS_SCHMITT_EN_REG(pin));
		arg = !!(val & PADS_SCHMITT_EN_BIT(pin));
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		val = pctl_readl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_HIGHZ;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		val = pctl_readl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_UP;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		val = pctl_readl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_DOWN;
		break;
	case PIN_CONFIG_BIAS_BUS_HOLD:
		val = pctl_readl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_BUS;
		break;
	case PIN_CONFIG_SLEW_RATE:
		val = pctl_readl(pctl, PADS_SLEW_RATE_REG(pin));
		arg = !!(val & PADS_SLEW_RATE_BIT(pin));
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		val = pctl_readl(pctl, PADS_DRIVE_STRENGTH_REG(pin)) >>
			PADS_DRIVE_STRENGTH_SHIFT(pin);
		switch (val & PADS_DRIVE_STRENGTH_MASK) {
		case PADS_DRIVE_STRENGTH_2MA:
			arg = 2;
			break;
		case PADS_DRIVE_STRENGTH_4MA:
			arg = 4;
			break;
		case PADS_DRIVE_STRENGTH_8MA:
			arg = 8;
			break;
		case PADS_DRIVE_STRENGTH_12MA:
		default:
			arg = 12;
			break;
		}
		break;
	default:
		dev_dbg(pctl->dev, "Property %u not supported\n", param);
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}