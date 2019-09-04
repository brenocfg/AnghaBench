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
struct mtk_pinctrl {int /*<<< orphan*/  chip; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 134 
#define  PIN_CONFIG_BIAS_PULL_DOWN 133 
#define  PIN_CONFIG_BIAS_PULL_UP 132 
#define  PIN_CONFIG_DRIVE_STRENGTH 131 
#define  PIN_CONFIG_INPUT_ENABLE 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  mtk_gpio_set (int /*<<< orphan*/ ,unsigned int,int) ; 
 int mtk_pconf_set_driving (struct mtk_pinctrl*,unsigned int,int) ; 
 int mtk_pconf_set_ies_smt (struct mtk_pinctrl*,unsigned int,int,int) ; 
 int mtk_pconf_set_pull_select (struct mtk_pinctrl*,unsigned int,int,int,int) ; 
 int mtk_pmx_gpio_set_direction (struct pinctrl_dev*,int /*<<< orphan*/ *,unsigned int,int) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pconf_parse_conf(struct pinctrl_dev *pctldev,
		unsigned int pin, enum pin_config_param param,
		enum pin_config_param arg)
{
	int ret = 0;
	struct mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		ret = mtk_pconf_set_pull_select(pctl, pin, false, false, arg);
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		ret = mtk_pconf_set_pull_select(pctl, pin, true, true, arg);
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		ret = mtk_pconf_set_pull_select(pctl, pin, true, false, arg);
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		mtk_pmx_gpio_set_direction(pctldev, NULL, pin, true);
		ret = mtk_pconf_set_ies_smt(pctl, pin, arg, param);
		break;
	case PIN_CONFIG_OUTPUT:
		mtk_gpio_set(pctl->chip, pin, arg);
		ret = mtk_pmx_gpio_set_direction(pctldev, NULL, pin, false);
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		mtk_pmx_gpio_set_direction(pctldev, NULL, pin, true);
		ret = mtk_pconf_set_ies_smt(pctl, pin, arg, param);
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		ret = mtk_pconf_set_driving(pctl, pin, arg);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}