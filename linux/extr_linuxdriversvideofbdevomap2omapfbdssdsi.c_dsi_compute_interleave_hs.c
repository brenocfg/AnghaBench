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

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static int dsi_compute_interleave_hs(int blank, bool ddr_alwon, int enter_hs,
		int exit_hs, int exiths_clk, int ddr_pre, int ddr_post)
{
	int transition;

	/*
	 * If DDR_CLK_ALWAYS_ON is set, we need to consider HS mode transition
	 * time of data lanes only, if it isn't set, we need to consider HS
	 * transition time of both data and clock lanes. HS transition time
	 * of Scenario 3 is considered.
	 */
	if (ddr_alwon) {
		transition = enter_hs + exit_hs + max(enter_hs, 2) + 1;
	} else {
		int trans1, trans2;
		trans1 = ddr_pre + enter_hs + exit_hs + max(enter_hs, 2) + 1;
		trans2 = ddr_pre + enter_hs + exiths_clk + ddr_post + ddr_pre +
				enter_hs + 1;
		transition = max(trans1, trans2);
	}

	return blank > transition ? blank - transition : 0;
}