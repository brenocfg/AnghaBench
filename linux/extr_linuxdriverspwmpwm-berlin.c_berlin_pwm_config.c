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
typedef  int u64 ;
typedef  int u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct berlin_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BERLIN_PWM_CONTROL ; 
 int /*<<< orphan*/  BERLIN_PWM_DUTY ; 
 int BERLIN_PWM_MAX_TCNT ; 
 int BERLIN_PWM_PRESCALE_4096 ; 
 int /*<<< orphan*/  BERLIN_PWM_TCNT ; 
 int ERANGE ; 
 int NSEC_PER_SEC ; 
 int berlin_pwm_readl (struct berlin_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  berlin_pwm_writel (struct berlin_pwm_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct berlin_pwm_chip* to_berlin_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int berlin_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm_dev,
			     int duty_ns, int period_ns)
{
	struct berlin_pwm_chip *pwm = to_berlin_pwm_chip(chip);
	bool prescale_4096 = false;
	u32 value, duty, period;
	u64 cycles;

	cycles = clk_get_rate(pwm->clk);
	cycles *= period_ns;
	do_div(cycles, NSEC_PER_SEC);

	if (cycles > BERLIN_PWM_MAX_TCNT) {
		prescale_4096 = true;
		cycles >>= 12; // Prescaled by 4096

		if (cycles > BERLIN_PWM_MAX_TCNT)
			return -ERANGE;
	}

	period = cycles;
	cycles *= duty_ns;
	do_div(cycles, period_ns);
	duty = cycles;

	value = berlin_pwm_readl(pwm, pwm_dev->hwpwm, BERLIN_PWM_CONTROL);
	if (prescale_4096)
		value |= BERLIN_PWM_PRESCALE_4096;
	else
		value &= ~BERLIN_PWM_PRESCALE_4096;
	berlin_pwm_writel(pwm, pwm_dev->hwpwm, value, BERLIN_PWM_CONTROL);

	berlin_pwm_writel(pwm, pwm_dev->hwpwm, duty, BERLIN_PWM_DUTY);
	berlin_pwm_writel(pwm, pwm_dev->hwpwm, period, BERLIN_PWM_TCNT);

	return 0;
}