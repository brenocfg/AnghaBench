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
typedef  int u8 ;
struct pwm_device {int /*<<< orphan*/  label; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TWL6030_LED_MAX ; 
 int /*<<< orphan*/  TWL6030_LED_PWM_CTRL1 ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_pwmled_config(struct pwm_chip *chip, struct pwm_device *pwm,
			      int duty_ns, int period_ns)
{
	int duty_cycle = (duty_ns * TWL6030_LED_MAX) / period_ns;
	u8 on_time;
	int ret;

	on_time = duty_cycle & 0xff;

	ret = twl_i2c_write_u8(TWL6030_MODULE_ID1, on_time,
			       TWL6030_LED_PWM_CTRL1);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to configure PWM\n", pwm->label);

	return ret;
}