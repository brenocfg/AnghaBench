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
struct rfbi_timings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 scalar_t__ calc_reg_timing (struct rfbi_timings*,int) ; 
 int /*<<< orphan*/  extif_clk_period ; 
 int /*<<< orphan*/  rfbi_get_clk_info (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int calc_extif_timings(struct rfbi_timings *t)
{
	u32 max_clk_div;
	int div;

	rfbi_get_clk_info(&extif_clk_period, &max_clk_div);
	for (div = 1; div <= max_clk_div; div++) {
		if (calc_reg_timing(t, div) == 0)
			break;
	}

	if (div <= max_clk_div)
		return 0;

	DSSERR("can't setup timings\n");
	return -1;
}