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
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_CTRL_ADDR (int /*<<< orphan*/ ) ; 
 int PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  PWM_POLARITY_MASK ; 
 int PWM_POLARITY_SHIFT ; 
 int /*<<< orphan*/  hibvt_pwm_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hibvt_pwm_chip* to_hibvt_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void hibvt_pwm_set_polarity(struct pwm_chip *chip,
					struct pwm_device *pwm,
					enum pwm_polarity polarity)
{
	struct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	if (polarity == PWM_POLARITY_INVERSED)
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
				PWM_POLARITY_MASK, (0x1 << PWM_POLARITY_SHIFT));
	else
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
				PWM_POLARITY_MASK, (0x0 << PWM_POLARITY_SHIFT));
}