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
typedef  unsigned long u32 ;
struct pwm_state {unsigned long long period; unsigned long long duty_cycle; scalar_t__ polarity; scalar_t__ enabled; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct imx_chip {int /*<<< orphan*/  clk_per; scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ MX3_PWMCR ; 
 unsigned long MX3_PWMCR_CLKSRC_IPG_HIGH ; 
 unsigned long MX3_PWMCR_DBGEN ; 
 unsigned long MX3_PWMCR_DOZEEN ; 
 unsigned long MX3_PWMCR_EN ; 
 unsigned long MX3_PWMCR_POUTC ; 
 unsigned long MX3_PWMCR_PRESCALER (unsigned long) ; 
 unsigned long MX3_PWMCR_STOPEN ; 
 unsigned long MX3_PWMCR_WAITEN ; 
 scalar_t__ MX3_PWMPR ; 
 scalar_t__ MX3_PWMSAR ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  imx_pwm_sw_reset (struct pwm_chip*) ; 
 int /*<<< orphan*/  imx_pwm_wait_fifo_slot (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 struct imx_chip* to_imx_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int imx_pwm_apply_v2(struct pwm_chip *chip, struct pwm_device *pwm,
			    struct pwm_state *state)
{
	unsigned long period_cycles, duty_cycles, prescale;
	struct imx_chip *imx = to_imx_chip(chip);
	struct pwm_state cstate;
	unsigned long long c;
	int ret;
	u32 cr;

	pwm_get_state(pwm, &cstate);

	if (state->enabled) {
		c = clk_get_rate(imx->clk_per);
		c *= state->period;

		do_div(c, 1000000000);
		period_cycles = c;

		prescale = period_cycles / 0x10000 + 1;

		period_cycles /= prescale;
		c = (unsigned long long)period_cycles * state->duty_cycle;
		do_div(c, state->period);
		duty_cycles = c;

		/*
		 * according to imx pwm RM, the real period value should be
		 * PERIOD value in PWMPR plus 2.
		 */
		if (period_cycles > 2)
			period_cycles -= 2;
		else
			period_cycles = 0;

		/*
		 * Wait for a free FIFO slot if the PWM is already enabled, and
		 * flush the FIFO if the PWM was disabled and is about to be
		 * enabled.
		 */
		if (cstate.enabled) {
			imx_pwm_wait_fifo_slot(chip, pwm);
		} else {
			ret = clk_prepare_enable(imx->clk_per);
			if (ret)
				return ret;

			imx_pwm_sw_reset(chip);
		}

		writel(duty_cycles, imx->mmio_base + MX3_PWMSAR);
		writel(period_cycles, imx->mmio_base + MX3_PWMPR);

		cr = MX3_PWMCR_PRESCALER(prescale) |
		     MX3_PWMCR_STOPEN | MX3_PWMCR_DOZEEN | MX3_PWMCR_WAITEN |
		     MX3_PWMCR_DBGEN | MX3_PWMCR_CLKSRC_IPG_HIGH |
		     MX3_PWMCR_EN;

		if (state->polarity == PWM_POLARITY_INVERSED)
			cr |= MX3_PWMCR_POUTC;

		writel(cr, imx->mmio_base + MX3_PWMCR);
	} else if (cstate.enabled) {
		writel(0, imx->mmio_base + MX3_PWMCR);

		clk_disable_unprepare(imx->clk_per);
	}

	return 0;
}