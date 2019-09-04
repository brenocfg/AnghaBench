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
typedef  int u64 ;
typedef  int u32 ;
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct mtk_pwm_chip {TYPE_1__* soc; struct clk** clks; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {scalar_t__ pwm45_fixup; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int EINVAL ; 
 size_t MTK_CLK_PWM1 ; 
 scalar_t__ NSEC_PER_SEC ; 
 int PWM45DWIDTH_FIXUP ; 
 int PWM45THRES_FIXUP ; 
 int PWMCON ; 
 int PWMDWIDTH ; 
 int PWMTHRES ; 
 int PWM_CLK_DIV_MAX ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pwm_clk_disable (struct pwm_chip*,struct pwm_device*) ; 
 int mtk_pwm_clk_enable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  mtk_pwm_writel (struct mtk_pwm_chip*,int,int,int) ; 
 struct mtk_pwm_chip* to_mtk_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int mtk_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			  int duty_ns, int period_ns)
{
	struct mtk_pwm_chip *pc = to_mtk_pwm_chip(chip);
	struct clk *clk = pc->clks[MTK_CLK_PWM1 + pwm->hwpwm];
	u32 clkdiv = 0, cnt_period, cnt_duty, reg_width = PWMDWIDTH,
	    reg_thres = PWMTHRES;
	u64 resolution;
	int ret;

	ret = mtk_pwm_clk_enable(chip, pwm);
	if (ret < 0)
		return ret;

	/* Using resolution in picosecond gets accuracy higher */
	resolution = (u64)NSEC_PER_SEC * 1000;
	do_div(resolution, clk_get_rate(clk));

	cnt_period = DIV_ROUND_CLOSEST_ULL((u64)period_ns * 1000, resolution);
	while (cnt_period > 8191) {
		resolution *= 2;
		clkdiv++;
		cnt_period = DIV_ROUND_CLOSEST_ULL((u64)period_ns * 1000,
						   resolution);
	}

	if (clkdiv > PWM_CLK_DIV_MAX) {
		mtk_pwm_clk_disable(chip, pwm);
		dev_err(chip->dev, "period %d not supported\n", period_ns);
		return -EINVAL;
	}

	if (pc->soc->pwm45_fixup && pwm->hwpwm > 2) {
		/*
		 * PWM[4,5] has distinct offset for PWMDWIDTH and PWMTHRES
		 * from the other PWMs on MT7623.
		 */
		reg_width = PWM45DWIDTH_FIXUP;
		reg_thres = PWM45THRES_FIXUP;
	}

	cnt_duty = DIV_ROUND_CLOSEST_ULL((u64)duty_ns * 1000, resolution);
	mtk_pwm_writel(pc, pwm->hwpwm, PWMCON, BIT(15) | clkdiv);
	mtk_pwm_writel(pc, pwm->hwpwm, reg_width, cnt_period);
	mtk_pwm_writel(pc, pwm->hwpwm, reg_thres, cnt_duty);

	mtk_pwm_clk_disable(chip, pwm);

	return 0;
}