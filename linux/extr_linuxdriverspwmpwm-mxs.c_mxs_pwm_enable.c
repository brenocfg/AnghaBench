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
struct pwm_device {int hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct mxs_pwm_chip {scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ PWM_CTRL ; 
 scalar_t__ SET ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mxs_pwm_chip* to_mxs_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct mxs_pwm_chip *mxs = to_mxs_pwm_chip(chip);
	int ret;

	ret = clk_prepare_enable(mxs->clk);
	if (ret)
		return ret;

	writel(1 << pwm->hwpwm, mxs->base + PWM_CTRL + SET);

	return 0;
}