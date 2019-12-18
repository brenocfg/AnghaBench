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
struct clk_aic32x4 {int dummy; } ;

/* Variables and functions */
 unsigned long clk_aic32x4_pll_calc_rate (struct clk_aic32x4_pll_muldiv*,unsigned long) ; 
 int clk_aic32x4_pll_get_muldiv (struct clk_aic32x4*,struct clk_aic32x4_pll_muldiv*) ; 
 struct clk_aic32x4* to_clk_aic32x4 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_aic32x4_pll_recalc_rate(struct clk_hw *hw,
			unsigned long parent_rate)
{
	struct clk_aic32x4 *pll = to_clk_aic32x4(hw);
	struct clk_aic32x4_pll_muldiv settings;
	int ret;

	ret =  clk_aic32x4_pll_get_muldiv(pll, &settings);
	if (ret < 0)
		return 0;

	return clk_aic32x4_pll_calc_rate(&settings, parent_rate);
}