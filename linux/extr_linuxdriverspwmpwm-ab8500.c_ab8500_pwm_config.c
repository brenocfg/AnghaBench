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
typedef  scalar_t__ u8 ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_MISC ; 
 scalar_t__ AB8500_PWM_OUT_CTRL1_REG ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ab8500_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			     int duty_ns, int period_ns)
{
	int ret = 0;
	unsigned int higher_val, lower_val;
	u8 reg;

	/*
	 * get the first 8 bits that are be written to
	 * AB8500_PWM_OUT_CTRL1_REG[0:7]
	 */
	lower_val = duty_ns & 0x00FF;
	/*
	 * get bits [9:10] that are to be written to
	 * AB8500_PWM_OUT_CTRL2_REG[0:1]
	 */
	higher_val = ((duty_ns & 0x0300) >> 8);

	reg = AB8500_PWM_OUT_CTRL1_REG + ((chip->base - 1) * 2);

	ret = abx500_set_register_interruptible(chip->dev, AB8500_MISC,
			reg, (u8)lower_val);
	if (ret < 0)
		return ret;
	ret = abx500_set_register_interruptible(chip->dev, AB8500_MISC,
			(reg + 1), (u8)higher_val);

	return ret;
}