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
struct clk_hw {int dummy; } ;
struct clk_aic32x4_pll_muldiv {int dummy; } ;

/* Variables and functions */
 int clk_aic32x4_pll_calc_muldiv (struct clk_aic32x4_pll_muldiv*,unsigned long,unsigned long) ; 
 long clk_aic32x4_pll_calc_rate (struct clk_aic32x4_pll_muldiv*,unsigned long) ; 

__attribute__((used)) static long clk_aic32x4_pll_round_rate(struct clk_hw *hw,
			unsigned long rate,
			unsigned long *parent_rate)
{
	struct clk_aic32x4_pll_muldiv settings;
	int ret;

	ret = clk_aic32x4_pll_calc_muldiv(&settings, rate, *parent_rate);
	if (ret < 0)
		return 0;

	return clk_aic32x4_pll_calc_rate(&settings, *parent_rate);
}