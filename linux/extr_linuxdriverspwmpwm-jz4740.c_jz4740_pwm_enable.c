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

/* Variables and functions */
 int /*<<< orphan*/  JZ_TIMER_CTRL_PWM_ENABLE ; 
 int /*<<< orphan*/  jz4740_timer_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_timer_get_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_timer_set_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	uint32_t ctrl = jz4740_timer_get_ctrl(pwm->pwm);

	ctrl |= JZ_TIMER_CTRL_PWM_ENABLE;
	jz4740_timer_set_ctrl(pwm->hwpwm, ctrl);
	jz4740_timer_enable(pwm->hwpwm);

	return 0;
}