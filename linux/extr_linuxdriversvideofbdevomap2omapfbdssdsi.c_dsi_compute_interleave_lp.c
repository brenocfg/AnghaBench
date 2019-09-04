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

__attribute__((used)) static int dsi_compute_interleave_lp(int blank, int enter_hs, int exit_hs,
		int lp_clk_div, int tdsi_fclk)
{
	int trans_lp;	/* time required for a LP transition, in TXBYTECLKHS */
	int tlp_avail;	/* time left for interleaving commands, in CLKIN4DDR */
	int ttxclkesc;	/* period of LP transmit escape clock, in CLKIN4DDR */
	int thsbyte_clk = 16;	/* Period of TXBYTECLKHS clock, in CLKIN4DDR */
	int lp_inter;	/* cmd mode data that can be interleaved, in bytes */

	/* maximum LP transition time according to Scenario 1 */
	trans_lp = exit_hs + max(enter_hs, 2) + 1;

	/* CLKIN4DDR = 16 * TXBYTECLKHS */
	tlp_avail = thsbyte_clk * (blank - trans_lp);

	ttxclkesc = tdsi_fclk * lp_clk_div;

	lp_inter = ((tlp_avail - 8 * thsbyte_clk - 5 * tdsi_fclk) / ttxclkesc -
			26) / 16;

	return max(lp_inter, 0);
}