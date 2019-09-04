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
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  MTK_PIN_CONFIG_RDSEL 137 
#define  MTK_PIN_CONFIG_TDSEL 136 
 int PINCTRL_PIN_REG_DIR ; 
 int PINCTRL_PIN_REG_E4 ; 
 int PINCTRL_PIN_REG_E8 ; 
 int PINCTRL_PIN_REG_PD ; 
 int PINCTRL_PIN_REG_PU ; 
 int PINCTRL_PIN_REG_RDSEL ; 
 int PINCTRL_PIN_REG_SMT ; 
 int PINCTRL_PIN_REG_SR ; 
 int PINCTRL_PIN_REG_TDSEL ; 
#define  PIN_CONFIG_BIAS_DISABLE 135 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 130 
#define  PIN_CONFIG_OUTPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int mtk_hw_get_value (struct mtk_pinctrl*,unsigned int,int,int*) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pinconf_get(struct pinctrl_dev *pctldev,
			   unsigned int pin, unsigned long *config)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	int val, val2, err, reg, ret = 1;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_PU, &val);
		if (err)
			return err;

		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_PD, &val2);
		if (err)
			return err;

		if (val || val2)
			return -EINVAL;

		break;
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_SLEW_RATE:
		reg = (param == PIN_CONFIG_BIAS_PULL_UP) ?
		      PINCTRL_PIN_REG_PU :
		      (param == PIN_CONFIG_BIAS_PULL_DOWN) ?
		      PINCTRL_PIN_REG_PD : PINCTRL_PIN_REG_SR;

		err = mtk_hw_get_value(hw, pin, reg, &val);
		if (err)
			return err;

		if (!val)
			return -EINVAL;

		break;
	case PIN_CONFIG_INPUT_ENABLE:
	case PIN_CONFIG_OUTPUT_ENABLE:
		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_DIR, &val);
		if (err)
			return err;

		/* HW takes input mode as zero; output mode as non-zero */
		if ((val && param == PIN_CONFIG_INPUT_ENABLE) ||
		    (!val && param == PIN_CONFIG_OUTPUT_ENABLE))
			return -EINVAL;

		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_DIR, &val);
		if (err)
			return err;

		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_SMT, &val2);
		if (err)
			return err;

		if (val || !val2)
			return -EINVAL;

		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_E4, &val);
		if (err)
			return err;

		err = mtk_hw_get_value(hw, pin, PINCTRL_PIN_REG_E8, &val2);
		if (err)
			return err;

		/* 4mA when (e8, e4) = (0, 0); 8mA when (e8, e4) = (0, 1)
		 * 12mA when (e8, e4) = (1, 0); 16mA when (e8, e4) = (1, 1)
		 */
		ret = ((val2 << 1) + val + 1) * 4;

		break;
	case MTK_PIN_CONFIG_TDSEL:
	case MTK_PIN_CONFIG_RDSEL:
		reg = (param == MTK_PIN_CONFIG_TDSEL) ?
		       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;

		err = mtk_hw_get_value(hw, pin, reg, &val);
		if (err)
			return err;

		ret = val;

		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, ret);

	return 0;
}