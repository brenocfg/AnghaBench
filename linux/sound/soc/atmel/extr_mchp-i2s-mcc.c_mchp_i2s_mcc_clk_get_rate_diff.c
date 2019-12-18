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
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned int abs (unsigned long) ; 
 long clk_round_rate (struct clk*,unsigned long) ; 

__attribute__((used)) static int mchp_i2s_mcc_clk_get_rate_diff(struct clk *clk,
					  unsigned long rate,
					  struct clk **best_clk,
					  unsigned long *best_rate,
					  unsigned long *best_diff_rate)
{
	long round_rate;
	unsigned int diff_rate;

	round_rate = clk_round_rate(clk, rate);
	if (round_rate < 0)
		return (int)round_rate;

	diff_rate = abs(rate - round_rate);
	if (diff_rate < *best_diff_rate) {
		*best_clk = clk;
		*best_diff_rate = diff_rate;
		*best_rate = rate;
	}

	return 0;
}