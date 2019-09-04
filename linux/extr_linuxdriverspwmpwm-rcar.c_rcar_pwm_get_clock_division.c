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
struct rcar_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ NSEC_PER_SEC ; 
 unsigned long long RCAR_PWM_MAX_CYCLE ; 
 unsigned int RCAR_PWM_MAX_DIVISION ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static int rcar_pwm_get_clock_division(struct rcar_pwm_chip *rp, int period_ns)
{
	unsigned long clk_rate = clk_get_rate(rp->clk);
	unsigned long long max; /* max cycle / nanoseconds */
	unsigned int div;

	if (clk_rate == 0)
		return -EINVAL;

	for (div = 0; div <= RCAR_PWM_MAX_DIVISION; div++) {
		max = (unsigned long long)NSEC_PER_SEC * RCAR_PWM_MAX_CYCLE *
			(1 << div);
		do_div(max, clk_rate);
		if (period_ns <= max)
			break;
	}

	return (div <= RCAR_PWM_MAX_DIVISION) ? div : -ERANGE;
}