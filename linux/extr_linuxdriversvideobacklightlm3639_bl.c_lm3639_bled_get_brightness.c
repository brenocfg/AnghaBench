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
struct lm3639_platform_data {int (* pwm_get_intensity ) () ;scalar_t__ pin_pwm; } ;
struct lm3639_chip_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; struct lm3639_platform_data* pdata; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BL_CONF_1 ; 
 int /*<<< orphan*/  REG_BL_CONF_3 ; 
 int /*<<< orphan*/  REG_BL_CONF_4 ; 
 struct lm3639_chip_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int stub1 () ; 

__attribute__((used)) static int lm3639_bled_get_brightness(struct backlight_device *bl)
{
	int ret;
	unsigned int reg_val;
	struct lm3639_chip_data *pchip = bl_get_data(bl);
	struct lm3639_platform_data *pdata = pchip->pdata;

	if (pdata->pin_pwm) {
		if (pdata->pwm_get_intensity)
			bl->props.brightness = pdata->pwm_get_intensity();
		else
			dev_err(pchip->dev,
				"No pwm control func. in plat-data\n");
		return bl->props.brightness;
	}

	ret = regmap_read(pchip->regmap, REG_BL_CONF_1, &reg_val);
	if (ret < 0)
		goto out;
	if (reg_val & 0x10)
		ret = regmap_read(pchip->regmap, REG_BL_CONF_4, &reg_val);
	else
		ret = regmap_read(pchip->regmap, REG_BL_CONF_3, &reg_val);
	if (ret < 0)
		goto out;
	bl->props.brightness = reg_val;

	return bl->props.brightness;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
	return bl->props.brightness;
}