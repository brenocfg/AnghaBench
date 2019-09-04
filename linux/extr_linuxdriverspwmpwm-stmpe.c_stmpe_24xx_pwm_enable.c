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
struct stmpe_pwm {int /*<<< orphan*/  stmpe; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMPE24XX_PWMCS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stmpe_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stmpe_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct stmpe_pwm* to_stmpe_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int stmpe_24xx_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct stmpe_pwm *stmpe_pwm = to_stmpe_pwm(chip);
	u8 value;
	int ret;

	ret = stmpe_reg_read(stmpe_pwm->stmpe, STMPE24XX_PWMCS);
	if (ret < 0) {
		dev_err(chip->dev, "error reading PWM#%u control\n",
			pwm->hwpwm);
		return ret;
	}

	value = ret | BIT(pwm->hwpwm);

	ret = stmpe_reg_write(stmpe_pwm->stmpe, STMPE24XX_PWMCS, value);
	if (ret) {
		dev_err(chip->dev, "error writing PWM#%u control\n",
			pwm->hwpwm);
		return ret;
	}

	return 0;
}