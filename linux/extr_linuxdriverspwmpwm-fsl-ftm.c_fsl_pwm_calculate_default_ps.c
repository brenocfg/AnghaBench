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
struct fsl_pwm_chip {size_t cnt_select; int clk_ps; int /*<<< orphan*/ * clk; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 int EINVAL ; 
#define  FSL_PWM_CLK_EXT 130 
#define  FSL_PWM_CLK_FIX 129 
#define  FSL_PWM_CLK_SYS 128 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static int fsl_pwm_calculate_default_ps(struct fsl_pwm_chip *fpc,
					enum fsl_pwm_clk index)
{
	unsigned long sys_rate, cnt_rate;
	unsigned long long ratio;

	sys_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_SYS]);
	if (!sys_rate)
		return -EINVAL;

	cnt_rate = clk_get_rate(fpc->clk[fpc->cnt_select]);
	if (!cnt_rate)
		return -EINVAL;

	switch (index) {
	case FSL_PWM_CLK_SYS:
		fpc->clk_ps = 1;
		break;
	case FSL_PWM_CLK_FIX:
		ratio = 2 * cnt_rate - 1;
		do_div(ratio, sys_rate);
		fpc->clk_ps = ratio;
		break;
	case FSL_PWM_CLK_EXT:
		ratio = 4 * cnt_rate - 1;
		do_div(ratio, sys_rate);
		fpc->clk_ps = ratio;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}