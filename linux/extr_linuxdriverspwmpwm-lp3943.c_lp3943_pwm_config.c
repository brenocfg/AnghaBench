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
struct pwm_device {scalar_t__ hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct lp3943_pwm {struct lp3943* lp3943; } ;
struct lp3943 {int dummy; } ;

/* Variables and functions */
 int LP3943_MAX_DUTY ; 
 int /*<<< orphan*/  LP3943_MAX_PERIOD ; 
 int LP3943_MIN_PERIOD ; 
 scalar_t__ LP3943_REG_PRESCALE0 ; 
 scalar_t__ LP3943_REG_PRESCALE1 ; 
 scalar_t__ LP3943_REG_PWM0 ; 
 scalar_t__ LP3943_REG_PWM1 ; 
 int clamp (int,int,int /*<<< orphan*/ ) ; 
 int lp3943_write_byte (struct lp3943*,scalar_t__,scalar_t__) ; 
 struct lp3943_pwm* to_lp3943_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int lp3943_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			     int duty_ns, int period_ns)
{
	struct lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	struct lp3943 *lp3943 = lp3943_pwm->lp3943;
	u8 val, reg_duty, reg_prescale;
	int err;

	/*
	 * How to configure the LP3943 PWMs
	 *
	 * 1) Period = 6250 ~ 1600000
	 * 2) Prescale = period / 6250 -1
	 * 3) Duty = input duty
	 *
	 * Prescale and duty are register values
	 */

	if (pwm->hwpwm == 0) {
		reg_prescale = LP3943_REG_PRESCALE0;
		reg_duty     = LP3943_REG_PWM0;
	} else {
		reg_prescale = LP3943_REG_PRESCALE1;
		reg_duty     = LP3943_REG_PWM1;
	}

	period_ns = clamp(period_ns, LP3943_MIN_PERIOD, LP3943_MAX_PERIOD);
	val       = (u8)(period_ns / LP3943_MIN_PERIOD - 1);

	err = lp3943_write_byte(lp3943, reg_prescale, val);
	if (err)
		return err;

	val = (u8)(duty_ns * LP3943_MAX_DUTY / period_ns);

	return lp3943_write_byte(lp3943, reg_duty, val);
}