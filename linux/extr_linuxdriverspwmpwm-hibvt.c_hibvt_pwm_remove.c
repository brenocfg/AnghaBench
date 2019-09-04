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
struct platform_device {int dummy; } ;
struct hibvt_pwm_chip {int /*<<< orphan*/  chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct hibvt_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hibvt_pwm_remove(struct platform_device *pdev)
{
	struct hibvt_pwm_chip *pwm_chip;

	pwm_chip = platform_get_drvdata(pdev);

	reset_control_assert(pwm_chip->rstc);
	msleep(30);
	reset_control_deassert(pwm_chip->rstc);

	clk_disable_unprepare(pwm_chip->clk);

	return pwmchip_remove(&pwm_chip->chip);
}