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
struct fsl_pwm_chip {int cnt_select; int /*<<< orphan*/ * clk; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 size_t FSL_PWM_CLK_EXT ; 
 size_t FSL_PWM_CLK_FIX ; 
 int FSL_PWM_CLK_SYS ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long fsl_pwm_calculate_period_cycles (struct fsl_pwm_chip*,unsigned long,int) ; 

__attribute__((used)) static unsigned long fsl_pwm_calculate_period(struct fsl_pwm_chip *fpc,
					      unsigned long period_ns)
{
	enum fsl_pwm_clk m0, m1;
	unsigned long fix_rate, ext_rate, cycles;

	cycles = fsl_pwm_calculate_period_cycles(fpc, period_ns,
			FSL_PWM_CLK_SYS);
	if (cycles) {
		fpc->cnt_select = FSL_PWM_CLK_SYS;
		return cycles;
	}

	fix_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_FIX]);
	ext_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_EXT]);

	if (fix_rate > ext_rate) {
		m0 = FSL_PWM_CLK_FIX;
		m1 = FSL_PWM_CLK_EXT;
	} else {
		m0 = FSL_PWM_CLK_EXT;
		m1 = FSL_PWM_CLK_FIX;
	}

	cycles = fsl_pwm_calculate_period_cycles(fpc, period_ns, m0);
	if (cycles) {
		fpc->cnt_select = m0;
		return cycles;
	}

	fpc->cnt_select = m1;

	return fsl_pwm_calculate_period_cycles(fpc, period_ns, m1);
}