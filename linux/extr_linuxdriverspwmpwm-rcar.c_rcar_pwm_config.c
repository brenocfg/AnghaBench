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
struct rcar_pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duty_cycle; } ;
struct pwm_device {TYPE_1__ state; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_PWMCR ; 
 int /*<<< orphan*/  RCAR_PWMCR_SYNC ; 
 int /*<<< orphan*/  pwm_is_enabled (struct pwm_device*) ; 
 int rcar_pwm_get_clock_division (struct rcar_pwm_chip*,int) ; 
 int /*<<< orphan*/  rcar_pwm_set_clock_control (struct rcar_pwm_chip*,int) ; 
 int rcar_pwm_set_counter (struct rcar_pwm_chip*,int,int,int) ; 
 int /*<<< orphan*/  rcar_pwm_update (struct rcar_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_pwm_chip* to_rcar_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int rcar_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			   int duty_ns, int period_ns)
{
	struct rcar_pwm_chip *rp = to_rcar_pwm_chip(chip);
	int div, ret;

	div = rcar_pwm_get_clock_division(rp, period_ns);
	if (div < 0)
		return div;

	/*
	 * Let the core driver set pwm->period if disabled and duty_ns == 0.
	 * But, this driver should prevent to set the new duty_ns if current
	 * duty_cycle is not set
	 */
	if (!pwm_is_enabled(pwm) && !duty_ns && !pwm->state.duty_cycle)
		return 0;

	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, RCAR_PWMCR_SYNC, RCAR_PWMCR);

	ret = rcar_pwm_set_counter(rp, div, duty_ns, period_ns);
	if (!ret)
		rcar_pwm_set_clock_control(rp, div);

	/* The SYNC should be set to 0 even if rcar_pwm_set_counter failed */
	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, 0, RCAR_PWMCR);

	return ret;
}