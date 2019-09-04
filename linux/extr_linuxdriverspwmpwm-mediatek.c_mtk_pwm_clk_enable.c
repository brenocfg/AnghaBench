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
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct mtk_pwm_chip {int /*<<< orphan*/ * clks; TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_clks; } ;

/* Variables and functions */
 size_t MTK_CLK_MAIN ; 
 size_t MTK_CLK_PWM1 ; 
 size_t MTK_CLK_TOP ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mtk_pwm_chip* to_mtk_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int mtk_pwm_clk_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct mtk_pwm_chip *pc = to_mtk_pwm_chip(chip);
	int ret;

	if (!pc->soc->has_clks)
		return 0;

	ret = clk_prepare_enable(pc->clks[MTK_CLK_TOP]);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(pc->clks[MTK_CLK_MAIN]);
	if (ret < 0)
		goto disable_clk_top;

	ret = clk_prepare_enable(pc->clks[MTK_CLK_PWM1 + pwm->hwpwm]);
	if (ret < 0)
		goto disable_clk_main;

	return 0;

disable_clk_main:
	clk_disable_unprepare(pc->clks[MTK_CLK_MAIN]);
disable_clk_top:
	clk_disable_unprepare(pc->clks[MTK_CLK_TOP]);

	return ret;
}