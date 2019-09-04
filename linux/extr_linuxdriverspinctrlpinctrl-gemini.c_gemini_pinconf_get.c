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
struct gemini_pmx {int /*<<< orphan*/  map; } ;
struct gemini_pin_conf {int mask; int /*<<< orphan*/  reg; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_SKEW_DELAY 128 
 int /*<<< orphan*/  ffs (int) ; 
 struct gemini_pin_conf* gemini_get_pin_conf (struct gemini_pmx*,unsigned int) ; 
 unsigned long pinconf_to_config_packed (int const,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct gemini_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int gemini_pinconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			      unsigned long *config)
{
	struct gemini_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	const struct gemini_pin_conf *conf;
	u32 val;

	switch (param) {
	case PIN_CONFIG_SKEW_DELAY:
		conf = gemini_get_pin_conf(pmx, pin);
		if (!conf)
			return -ENOTSUPP;
		regmap_read(pmx->map, conf->reg, &val);
		val &= conf->mask;
		val >>= (ffs(conf->mask) - 1);
		*config = pinconf_to_config_packed(PIN_CONFIG_SKEW_DELAY, val);
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}