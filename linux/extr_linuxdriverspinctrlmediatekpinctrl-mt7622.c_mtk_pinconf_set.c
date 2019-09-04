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
 int ENOTSUPP ; 
 int MTK_DISABLE ; 
 int MTK_OUTPUT ; 
#define  MTK_PIN_CONFIG_RDSEL 138 
#define  MTK_PIN_CONFIG_TDSEL 137 
 int PINCTRL_PIN_REG_DIR ; 
 int PINCTRL_PIN_REG_DO ; 
 int PINCTRL_PIN_REG_E4 ; 
 int PINCTRL_PIN_REG_E8 ; 
 int PINCTRL_PIN_REG_PD ; 
 int PINCTRL_PIN_REG_PU ; 
 int PINCTRL_PIN_REG_RDSEL ; 
 int PINCTRL_PIN_REG_SMT ; 
 int PINCTRL_PIN_REG_SR ; 
 int PINCTRL_PIN_REG_TDSEL ; 
#define  PIN_CONFIG_BIAS_DISABLE 136 
#define  PIN_CONFIG_BIAS_PULL_DOWN 135 
#define  PIN_CONFIG_BIAS_PULL_UP 134 
#define  PIN_CONFIG_DRIVE_STRENGTH 133 
#define  PIN_CONFIG_INPUT_ENABLE 132 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 131 
#define  PIN_CONFIG_OUTPUT 130 
#define  PIN_CONFIG_OUTPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int mtk_hw_set_value (struct mtk_pinctrl*,unsigned int,int,int) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
			   unsigned long *configs, unsigned int num_configs)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	u32 reg, param, arg;
	int cfg, err = 0;

	for (cfg = 0; cfg < num_configs; cfg++) {
		param = pinconf_to_config_param(configs[cfg]);
		arg = pinconf_to_config_argument(configs[cfg]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_BIAS_PULL_DOWN:
			arg = (param == PIN_CONFIG_BIAS_DISABLE) ? 0 :
			       (param == PIN_CONFIG_BIAS_PULL_UP) ? 1 : 2;

			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_PU,
					       arg & 1);
			if (err)
				goto err;

			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_PD,
					       !!(arg & 2));
			if (err)
				goto err;
			break;
		case PIN_CONFIG_OUTPUT_ENABLE:
			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_SMT,
					       MTK_DISABLE);
			if (err)
				goto err;
			/* else: fall through */
		case PIN_CONFIG_INPUT_ENABLE:
		case PIN_CONFIG_SLEW_RATE:
			reg = (param == PIN_CONFIG_SLEW_RATE) ?
			       PINCTRL_PIN_REG_SR : PINCTRL_PIN_REG_DIR;

			arg = (param == PIN_CONFIG_INPUT_ENABLE) ? 0 :
			      (param == PIN_CONFIG_OUTPUT_ENABLE) ? 1 : arg;
			err = mtk_hw_set_value(hw, pin, reg, arg);
			if (err)
				goto err;

			break;
		case PIN_CONFIG_OUTPUT:
			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_DIR,
					       MTK_OUTPUT);
			if (err)
				goto err;

			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_DO,
					       arg);
			if (err)
				goto err;
			break;
		case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			/* arg = 1: Input mode & SMT enable ;
			 * arg = 0: Output mode & SMT disable
			 */
			arg = arg ? 2 : 1;
			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_DIR,
					       arg & 1);
			if (err)
				goto err;

			err = mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_SMT,
					       !!(arg & 2));
			if (err)
				goto err;
			break;
		case PIN_CONFIG_DRIVE_STRENGTH:
			/* 4mA when (e8, e4) = (0, 0);
			 * 8mA when (e8, e4) = (0, 1);
			 * 12mA when (e8, e4) = (1, 0);
			 * 16mA when (e8, e4) = (1, 1)
			 */
			if (!(arg % 4) && (arg >= 4 && arg <= 16)) {
				arg = arg / 4 - 1;
				err = mtk_hw_set_value(hw, pin,
						       PINCTRL_PIN_REG_E4,
						       arg & 0x1);
				if (err)
					goto err;

				err = mtk_hw_set_value(hw, pin,
						       PINCTRL_PIN_REG_E8,
						       (arg & 0x2) >> 1);
				if (err)
					goto err;
			} else {
				err = -ENOTSUPP;
			}
			break;
		case MTK_PIN_CONFIG_TDSEL:
		case MTK_PIN_CONFIG_RDSEL:
			reg = (param == MTK_PIN_CONFIG_TDSEL) ?
			       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;

			err = mtk_hw_set_value(hw, pin, reg, arg);
			if (err)
				goto err;
			break;
		default:
			err = -ENOTSUPP;
		}
	}
err:
	return err;
}