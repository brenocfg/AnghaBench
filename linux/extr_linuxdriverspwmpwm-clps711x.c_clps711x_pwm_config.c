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
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct clps711x_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int clps711x_get_duty (struct pwm_device*,int) ; 
 int /*<<< orphan*/  clps711x_pwm_update_val (struct clps711x_chip*,int /*<<< orphan*/ ,unsigned int) ; 
 int pwm_get_period (struct pwm_device*) ; 
 struct clps711x_chip* to_clps711x_chip (struct pwm_chip*) ; 

__attribute__((used)) static int clps711x_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			       int duty_ns, int period_ns)
{
	struct clps711x_chip *priv = to_clps711x_chip(chip);
	unsigned int duty;

	if (period_ns != pwm_get_period(pwm))
		return -EINVAL;

	duty = clps711x_get_duty(pwm, duty_ns);
	clps711x_pwm_update_val(priv, pwm->hwpwm, duty);

	return 0;
}