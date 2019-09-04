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
struct gemini_pmx {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct gemini_pin_conf {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_SKEW_DELAY 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ffs (int /*<<< orphan*/ ) ; 
 struct gemini_pin_conf* gemini_get_pin_conf (struct gemini_pmx*,unsigned int) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct gemini_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gemini_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
			      unsigned long *configs, unsigned int num_configs)
{
	struct gemini_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	const struct gemini_pin_conf *conf;
	enum pin_config_param param;
	u32 arg;
	int ret = 0;
	int i;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_SKEW_DELAY:
			if (arg > 0xf)
				return -EINVAL;
			conf = gemini_get_pin_conf(pmx, pin);
			if (!conf) {
				dev_err(pmx->dev,
					"invalid pin for skew delay %d\n", pin);
				return -ENOTSUPP;
			}
			arg <<= (ffs(conf->mask) - 1);
			dev_dbg(pmx->dev,
				"set pin %d to skew delay mask %08x, val %08x\n",
				pin, conf->mask, arg);
			regmap_update_bits(pmx->map, conf->reg, conf->mask, arg);
			break;
		default:
			dev_err(pmx->dev, "Invalid config param %04x\n", param);
			return -ENOTSUPP;
		}
	}

	return ret;
}