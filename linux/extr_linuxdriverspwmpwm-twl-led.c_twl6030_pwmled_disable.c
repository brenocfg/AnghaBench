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
typedef  int /*<<< orphan*/  u8 ;
struct twl_pwmled_chip {int /*<<< orphan*/  mutex; } ;
struct pwm_device {int /*<<< orphan*/  label; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6030_LED_PWM_CTRL2 ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID1 ; 
 int /*<<< orphan*/  TWL6040_LED_MODE_MASK ; 
 int /*<<< orphan*/  TWL6040_LED_MODE_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl_pwmled_chip* to_twl (struct pwm_chip*) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl6030_pwmled_disable(struct pwm_chip *chip,
				   struct pwm_device *pwm)
{
	struct twl_pwmled_chip *twl = to_twl(chip);
	int ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_read_u8(TWL6030_MODULE_ID1, &val, TWL6030_LED_PWM_CTRL2);
	if (ret < 0) {
		dev_err(chip->dev, "%s: Failed to read PWM_CTRL2\n",
			pwm->label);
		goto out;
	}

	val &= ~TWL6040_LED_MODE_MASK;
	val |= TWL6040_LED_MODE_OFF;

	ret = twl_i2c_write_u8(TWL6030_MODULE_ID1, val, TWL6030_LED_PWM_CTRL2);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
}