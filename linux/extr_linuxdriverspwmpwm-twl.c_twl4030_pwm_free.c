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
struct twl_pwm_chip {int twl4030_pwm_mux; int /*<<< orphan*/  mutex; } ;
struct pwm_device {int hwpwm; int /*<<< orphan*/  label; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TWL4030_GPIO6_PWM0_MUTE_MASK ; 
 int TWL4030_GPIO7_VIBRASYNC_PWM1_MASK ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTBR ; 
 int /*<<< orphan*/  TWL4030_PMBR1_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl_pwm_chip* to_twl (struct pwm_chip*) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct twl_pwm_chip *twl = to_twl(chip);
	int ret;
	u8 val, mask;

	if (pwm->hwpwm == 1)
		mask = TWL4030_GPIO7_VIBRASYNC_PWM1_MASK;
	else
		mask = TWL4030_GPIO6_PWM0_MUTE_MASK;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_read_u8(TWL4030_MODULE_INTBR, &val, TWL4030_PMBR1_REG);
	if (ret < 0) {
		dev_err(chip->dev, "%s: Failed to read PMBR1\n", pwm->label);
		goto out;
	}

	/* Restore the MUX configuration for the PWM */
	val &= ~mask;
	val |= (twl->twl4030_pwm_mux & mask);

	ret = twl_i2c_write_u8(TWL4030_MODULE_INTBR, val, TWL4030_PMBR1_REG);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to free PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
}