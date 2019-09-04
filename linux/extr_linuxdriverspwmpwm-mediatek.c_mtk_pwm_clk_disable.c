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
 struct mtk_pwm_chip* to_mtk_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void mtk_pwm_clk_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct mtk_pwm_chip *pc = to_mtk_pwm_chip(chip);

	if (!pc->soc->has_clks)
		return;

	clk_disable_unprepare(pc->clks[MTK_CLK_PWM1 + pwm->hwpwm]);
	clk_disable_unprepare(pc->clks[MTK_CLK_MAIN]);
	clk_disable_unprepare(pc->clks[MTK_CLK_TOP]);
}