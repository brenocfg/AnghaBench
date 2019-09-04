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

/* Variables and functions */
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static unsigned long fsl_pwm_calculate_cycles(struct fsl_pwm_chip *fpc,
					      unsigned long period_ns)
{
	unsigned long long c, c0;

	c = clk_get_rate(fpc->clk[fpc->cnt_select]);
	c = c * period_ns;
	do_div(c, 1000000000UL);

	do {
		c0 = c;
		do_div(c0, (1 << fpc->clk_ps));
		if (c0 <= 0xFFFF)
			return (unsigned long)c0;
	} while (++fpc->clk_ps < 8);

	return 0;
}