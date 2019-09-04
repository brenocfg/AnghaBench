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
struct hibvt_pwm_chip {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_CTRL_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWM_ENABLE_MASK ; 
 int /*<<< orphan*/  hibvt_pwm_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hibvt_pwm_chip* to_hibvt_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void hibvt_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
			PWM_ENABLE_MASK, 0x0);
}