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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pwm_chip {int /*<<< orphan*/  clk; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_ENABLE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_readl (struct tegra_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_writel (struct tegra_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_pwm_chip* to_tegra_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int tegra_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct tegra_pwm_chip *pc = to_tegra_pwm_chip(chip);
	int rc = 0;
	u32 val;

	rc = clk_prepare_enable(pc->clk);
	if (rc < 0)
		return rc;

	val = pwm_readl(pc, pwm->hwpwm);
	val |= PWM_ENABLE;
	pwm_writel(pc, pwm->hwpwm, val);

	return 0;
}