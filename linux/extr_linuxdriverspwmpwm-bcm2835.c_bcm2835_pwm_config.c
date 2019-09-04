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
struct bcm2835_pwm {scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ DUTY (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MIN_PERIOD ; 
 unsigned long NSEC_PER_SEC ; 
 scalar_t__ PERIOD (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct bcm2835_pwm* to_bcm2835_pwm (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm2835_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			      int duty_ns, int period_ns)
{
	struct bcm2835_pwm *pc = to_bcm2835_pwm(chip);
	unsigned long rate = clk_get_rate(pc->clk);
	unsigned long scaler;

	if (!rate) {
		dev_err(pc->dev, "failed to get clock rate\n");
		return -EINVAL;
	}

	scaler = NSEC_PER_SEC / rate;

	if (period_ns <= MIN_PERIOD) {
		dev_err(pc->dev, "period %d not supported, minimum %d\n",
			period_ns, MIN_PERIOD);
		return -EINVAL;
	}

	writel(duty_ns / scaler, pc->base + DUTY(pwm->hwpwm));
	writel(period_ns / scaler, pc->base + PERIOD(pwm->hwpwm));

	return 0;
}