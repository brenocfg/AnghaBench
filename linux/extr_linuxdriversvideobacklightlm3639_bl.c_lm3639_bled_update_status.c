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
struct lm3639_platform_data {int /*<<< orphan*/  max_brt_led; int /*<<< orphan*/  (* pwm_set_intensity ) (int,int /*<<< orphan*/ ) ;scalar_t__ pin_pwm; } ;
struct lm3639_chip_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; struct lm3639_platform_data* pdata; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BL_CONF_3 ; 
 int /*<<< orphan*/  REG_BL_CONF_4 ; 
 int /*<<< orphan*/  REG_ENABLE ; 
 int /*<<< orphan*/  REG_FLAG ; 
 struct lm3639_chip_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3639_bled_update_status(struct backlight_device *bl)
{
	int ret;
	unsigned int reg_val;
	struct lm3639_chip_data *pchip = bl_get_data(bl);
	struct lm3639_platform_data *pdata = pchip->pdata;

	ret = regmap_read(pchip->regmap, REG_FLAG, &reg_val);
	if (ret < 0)
		goto out;

	if (reg_val != 0)
		dev_info(pchip->dev, "last flag is 0x%x\n", reg_val);

	/* pwm control */
	if (pdata->pin_pwm) {
		if (pdata->pwm_set_intensity)
			pdata->pwm_set_intensity(bl->props.brightness,
						 pdata->max_brt_led);
		else
			dev_err(pchip->dev,
				"No pwm control func. in plat-data\n");
		return bl->props.brightness;
	}

	/* i2c control and set brigtness */
	ret = regmap_write(pchip->regmap, REG_BL_CONF_4, bl->props.brightness);
	if (ret < 0)
		goto out;
	ret = regmap_write(pchip->regmap, REG_BL_CONF_3, bl->props.brightness);
	if (ret < 0)
		goto out;

	if (!bl->props.brightness)
		ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x01, 0x00);
	else
		ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x01, 0x01);
	if (ret < 0)
		goto out;

	return bl->props.brightness;
out:
	dev_err(pchip->dev, "i2c failed to access registers\n");
	return bl->props.brightness;
}