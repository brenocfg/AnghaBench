#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwm_state {scalar_t__ polarity; scalar_t__ period; scalar_t__ duty_cycle; scalar_t__ enabled; } ;
struct TYPE_2__ {scalar_t__ polarity; scalar_t__ period; scalar_t__ duty_cycle; scalar_t__ enabled; } ;
struct pwm_device {TYPE_1__ state; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hibvt_pwm_config (struct pwm_chip*,struct pwm_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hibvt_pwm_disable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  hibvt_pwm_enable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  hibvt_pwm_set_polarity (struct pwm_chip*,struct pwm_device*,scalar_t__) ; 

__attribute__((used)) static int hibvt_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
				struct pwm_state *state)
{
	if (state->polarity != pwm->state.polarity)
		hibvt_pwm_set_polarity(chip, pwm, state->polarity);

	if (state->period != pwm->state.period ||
		state->duty_cycle != pwm->state.duty_cycle)
		hibvt_pwm_config(chip, pwm, state->duty_cycle, state->period);

	if (state->enabled != pwm->state.enabled) {
		if (state->enabled)
			hibvt_pwm_enable(chip, pwm);
		else
			hibvt_pwm_disable(chip, pwm);
	}

	return 0;
}