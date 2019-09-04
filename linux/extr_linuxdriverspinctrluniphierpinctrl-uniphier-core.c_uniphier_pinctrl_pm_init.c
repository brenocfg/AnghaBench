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
struct uniphier_pinctrl_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int uniphier_pinctrl_pm_init(struct device *dev,
				    struct uniphier_pinctrl_priv *priv)
{
#ifdef CONFIG_PM_SLEEP
	const struct uniphier_pinctrl_socdata *socdata = priv->socdata;
	unsigned int num_drvctrl = 0;
	unsigned int num_drv2ctrl = 0;
	unsigned int num_drv3ctrl = 0;
	unsigned int num_pupdctrl = 0;
	unsigned int num_iectrl = 0;
	unsigned int iectrl, drvctrl, pupdctrl;
	enum uniphier_pin_drv_type drv_type;
	enum uniphier_pin_pull_dir pull_dir;
	int i, ret;

	for (i = 0; i < socdata->npins; i++) {
		void *drv_data = socdata->pins[i].drv_data;

		drvctrl = uniphier_pin_get_drvctrl(drv_data);
		drv_type = uniphier_pin_get_drv_type(drv_data);
		pupdctrl = uniphier_pin_get_pupdctrl(drv_data);
		pull_dir = uniphier_pin_get_pull_dir(drv_data);
		iectrl = uniphier_pin_get_iectrl(drv_data);

		switch (drv_type) {
		case UNIPHIER_PIN_DRV_1BIT:
			num_drvctrl = max(num_drvctrl, drvctrl + 1);
			break;
		case UNIPHIER_PIN_DRV_2BIT:
			num_drv2ctrl = max(num_drv2ctrl, drvctrl + 1);
			break;
		case UNIPHIER_PIN_DRV_3BIT:
			num_drv3ctrl = max(num_drv3ctrl, drvctrl + 1);
			break;
		default:
			break;
		}

		if (pull_dir == UNIPHIER_PIN_PULL_UP ||
		    pull_dir == UNIPHIER_PIN_PULL_DOWN)
			num_pupdctrl = max(num_pupdctrl, pupdctrl + 1);

		if (iectrl != UNIPHIER_PIN_IECTRL_NONE) {
			if (socdata->caps & UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL)
				iectrl = i;
			num_iectrl = max(num_iectrl, iectrl + 1);
		}
	}

	INIT_LIST_HEAD(&priv->reg_regions);

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_PINMUX_BASE,
					      socdata->npins, 8);
	if (ret)
		return ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRVCTRL_BASE,
					      num_drvctrl, 1);
	if (ret)
		return ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRV2CTRL_BASE,
					      num_drv2ctrl, 2);
	if (ret)
		return ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRV3CTRL_BASE,
					      num_drv3ctrl, 3);
	if (ret)
		return ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_PUPDCTRL_BASE,
					      num_pupdctrl, 1);
	if (ret)
		return ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_IECTRL_BASE,
					      num_iectrl, 1);
	if (ret)
		return ret;
#endif
	return 0;
}