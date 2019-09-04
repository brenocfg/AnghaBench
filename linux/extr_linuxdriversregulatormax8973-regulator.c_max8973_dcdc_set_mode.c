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
struct regulator_dev {int dummy; } ;
struct max8973_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX8973_CONTROL1 ; 
 int MAX8973_FPWM_EN_M ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct max8973_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max8973_dcdc_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct max8973_chip *max = rdev_get_drvdata(rdev);
	int ret;
	int pwm;

	/* Enable force PWM mode in FAST mode only. */
	switch (mode) {
	case REGULATOR_MODE_FAST:
		pwm = MAX8973_FPWM_EN_M;
		break;

	case REGULATOR_MODE_NORMAL:
		pwm = 0;
		break;

	default:
		return -EINVAL;
	}

	ret = regmap_update_bits(max->regmap, MAX8973_CONTROL1,
				MAX8973_FPWM_EN_M, pwm);
	if (ret < 0)
		dev_err(max->dev, "register %d update failed, err %d\n",
				MAX8973_CONTROL1, ret);
	return ret;
}