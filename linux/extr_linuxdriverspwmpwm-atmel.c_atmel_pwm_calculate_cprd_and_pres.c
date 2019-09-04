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
typedef  scalar_t__ u32 ;
struct pwm_state {unsigned long long period; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct atmel_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 scalar_t__ PRD_MAX_PRES ; 
 unsigned long long PWM_MAX_PRD ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int atmel_pwm_calculate_cprd_and_pres(struct pwm_chip *chip,
					     const struct pwm_state *state,
					     unsigned long *cprd, u32 *pres)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);
	unsigned long long cycles = state->period;

	/* Calculate the period cycles and prescale value */
	cycles *= clk_get_rate(atmel_pwm->clk);
	do_div(cycles, NSEC_PER_SEC);

	for (*pres = 0; cycles > PWM_MAX_PRD; cycles >>= 1)
		(*pres)++;

	if (*pres > PRD_MAX_PRES) {
		dev_err(chip->dev, "pres exceeds the maximum value\n");
		return -EINVAL;
	}

	*cprd = cycles;

	return 0;
}