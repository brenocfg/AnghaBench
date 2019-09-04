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
typedef  int u32 ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct bcm281xx_pinctrl_data {TYPE_1__* pins; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM281XX_PIN_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM281XX_PIN_SHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDMI ; 
 int /*<<< orphan*/  INPUT_DIS ; 
 int /*<<< orphan*/  MODE ; 
#define  PIN_CONFIG_INPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  bcm281xx_pin_update (int*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct bcm281xx_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int bcm281xx_hdmi_pin_update(struct pinctrl_dev *pctldev,
				    unsigned pin,
				    unsigned long *configs,
				    unsigned num_configs,
				    u32 *val,
				    u32 *mask)
{
	struct bcm281xx_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	int i;
	enum pin_config_param param;
	u32 arg;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_SLEW_RATE:
			arg = (arg >= 1 ? 1 : 0);
			bcm281xx_pin_update(val, mask, arg,
				BCM281XX_PIN_SHIFT(HDMI, MODE),
				BCM281XX_PIN_MASK(HDMI, MODE));
			break;

		case PIN_CONFIG_INPUT_ENABLE:
			/* inversed since register is for input _disable_ */
			arg = (arg >= 1 ? 0 : 1);
			bcm281xx_pin_update(val, mask, arg,
				BCM281XX_PIN_SHIFT(HDMI, INPUT_DIS),
				BCM281XX_PIN_MASK(HDMI, INPUT_DIS));
			break;

		default:
			dev_err(pctldev->dev,
				"Unrecognized pin config %d for pin %s (%d).\n",
				param, pdata->pins[pin].name, pin);
			return -EINVAL;

		} /* switch config */
	} /* for each config */

	return 0;
}