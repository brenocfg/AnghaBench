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
typedef  int /*<<< orphan*/  uint32_t ;
struct pwm_device {int /*<<< orphan*/  hwpwm; int /*<<< orphan*/  pwm; } ;
struct pwm_chip {int dummy; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_TIMER_CTRL_PWM_ACTIVE_LOW ; 
#define  PWM_POLARITY_INVERSED 129 
#define  PWM_POLARITY_NORMAL 128 
 int /*<<< orphan*/  jz4740_timer_get_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_timer_set_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_pwm_set_polarity(struct pwm_chip *chip,
		struct pwm_device *pwm, enum pwm_polarity polarity)
{
	uint32_t ctrl = jz4740_timer_get_ctrl(pwm->pwm);

	switch (polarity) {
	case PWM_POLARITY_NORMAL:
		ctrl &= ~JZ_TIMER_CTRL_PWM_ACTIVE_LOW;
		break;
	case PWM_POLARITY_INVERSED:
		ctrl |= JZ_TIMER_CTRL_PWM_ACTIVE_LOW;
		break;
	}

	jz4740_timer_set_ctrl(pwm->hwpwm, ctrl);
	return 0;
}