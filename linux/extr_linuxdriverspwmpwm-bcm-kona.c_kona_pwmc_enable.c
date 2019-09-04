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
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct kona_pwmc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int kona_pwmc_config (struct pwm_chip*,struct pwm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_get_duty_cycle (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_get_period (struct pwm_device*) ; 
 struct kona_pwmc* to_kona_pwmc (struct pwm_chip*) ; 

__attribute__((used)) static int kona_pwmc_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct kona_pwmc *kp = to_kona_pwmc(chip);
	int ret;

	ret = clk_prepare_enable(kp->clk);
	if (ret < 0) {
		dev_err(chip->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}

	ret = kona_pwmc_config(chip, pwm, pwm_get_duty_cycle(pwm),
			       pwm_get_period(pwm));
	if (ret < 0) {
		clk_disable_unprepare(kp->clk);
		return ret;
	}

	return 0;
}