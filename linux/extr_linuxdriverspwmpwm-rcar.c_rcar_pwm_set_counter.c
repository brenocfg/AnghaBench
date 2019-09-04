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
typedef  int u32 ;
struct rcar_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  RCAR_PWMCNT ; 
 unsigned long long RCAR_PWMCNT_CYC0_MASK ; 
 unsigned long long RCAR_PWMCNT_CYC0_SHIFT ; 
 unsigned long long RCAR_PWMCNT_PH0_MASK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  rcar_pwm_write (struct rcar_pwm_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pwm_set_counter(struct rcar_pwm_chip *rp, int div, int duty_ns,
				int period_ns)
{
	unsigned long long one_cycle, tmp;	/* 0.01 nanoseconds */
	unsigned long clk_rate = clk_get_rate(rp->clk);
	u32 cyc, ph;

	one_cycle = (unsigned long long)NSEC_PER_SEC * 100ULL * (1 << div);
	do_div(one_cycle, clk_rate);

	tmp = period_ns * 100ULL;
	do_div(tmp, one_cycle);
	cyc = (tmp << RCAR_PWMCNT_CYC0_SHIFT) & RCAR_PWMCNT_CYC0_MASK;

	tmp = duty_ns * 100ULL;
	do_div(tmp, one_cycle);
	ph = tmp & RCAR_PWMCNT_PH0_MASK;

	/* Avoid prohibited setting */
	if (cyc == 0 || ph == 0)
		return -EINVAL;

	rcar_pwm_write(rp, cyc | ph, RCAR_PWMCNT);

	return 0;
}