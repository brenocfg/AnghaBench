#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm3630a_chip {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_4__ {int brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
typedef  enum lm3630a_pwm_ctrl { ____Placeholder_lm3630a_pwm_ctrl } lm3630a_pwm_ctrl ;
struct TYPE_3__ {int pwm_ctrl; } ;

/* Variables and functions */
 int LM3630A_PWM_BANK_A ; 
 int /*<<< orphan*/  REG_BRT_A ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  REG_PWM_OUTHIGH ; 
 int /*<<< orphan*/  REG_PWM_OUTLOW ; 
 struct lm3630a_chip* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lm3630a_read (struct lm3630a_chip*,int /*<<< orphan*/ ) ; 
 int lm3630a_update (struct lm3630a_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lm3630a_bank_a_get_brightness(struct backlight_device *bl)
{
	int brightness, rval;
	struct lm3630a_chip *pchip = bl_get_data(bl);
	enum lm3630a_pwm_ctrl pwm_ctrl = pchip->pdata->pwm_ctrl;

	if ((pwm_ctrl & LM3630A_PWM_BANK_A) != 0) {
		rval = lm3630a_read(pchip, REG_PWM_OUTHIGH);
		if (rval < 0)
			goto out_i2c_err;
		brightness = (rval & 0x01) << 8;
		rval = lm3630a_read(pchip, REG_PWM_OUTLOW);
		if (rval < 0)
			goto out_i2c_err;
		brightness |= rval;
		goto out;
	}

	/* disable sleep */
	rval = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	if (rval < 0)
		goto out_i2c_err;
	usleep_range(1000, 2000);
	rval = lm3630a_read(pchip, REG_BRT_A);
	if (rval < 0)
		goto out_i2c_err;
	brightness = rval;

out:
	bl->props.brightness = brightness;
	return bl->props.brightness;
out_i2c_err:
	dev_err(pchip->dev, "i2c failed to access register\n");
	return 0;
}