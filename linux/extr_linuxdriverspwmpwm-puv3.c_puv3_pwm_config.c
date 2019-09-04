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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct puv3_pwm_chip {int /*<<< orphan*/  clk; scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long OST_PWMDCCR_FDCYCLE ; 
 scalar_t__ OST_PWM_DCCR ; 
 scalar_t__ OST_PWM_PCR ; 
 scalar_t__ OST_PWM_PWCR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 struct puv3_pwm_chip* to_puv3 (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int puv3_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			   int duty_ns, int period_ns)
{
	unsigned long period_cycles, prescale, pv, dc;
	struct puv3_pwm_chip *puv3 = to_puv3(chip);
	unsigned long long c;

	c = clk_get_rate(puv3->clk);
	c = c * period_ns;
	do_div(c, 1000000000);
	period_cycles = c;

	if (period_cycles < 1)
		period_cycles = 1;

	prescale = (period_cycles - 1) / 1024;
	pv = period_cycles / (prescale + 1) - 1;

	if (prescale > 63)
		return -EINVAL;

	if (duty_ns == period_ns)
		dc = OST_PWMDCCR_FDCYCLE;
	else
		dc = (pv + 1) * duty_ns / period_ns;

	/*
	 * NOTE: the clock to PWM has to be enabled first
	 * before writing to the registers
	 */
	clk_prepare_enable(puv3->clk);

	writel(prescale, puv3->base + OST_PWM_PWCR);
	writel(pv - dc, puv3->base + OST_PWM_DCCR);
	writel(pv, puv3->base + OST_PWM_PCR);

	clk_disable_unprepare(puv3->clk);

	return 0;
}