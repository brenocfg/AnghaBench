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
struct stm32_sai_sub_data {int dummy; } ;
struct stm32_sai_mclk_data {unsigned long freq; struct stm32_sai_sub_data* sai_data; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int stm32_sai_get_clk_div (struct stm32_sai_sub_data*,unsigned long,unsigned long) ; 
 int stm32_sai_set_clk_div (struct stm32_sai_sub_data*,int) ; 
 struct stm32_sai_mclk_data* to_mclk_data (struct clk_hw*) ; 

__attribute__((used)) static int stm32_sai_mclk_set_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long parent_rate)
{
	struct stm32_sai_mclk_data *mclk = to_mclk_data(hw);
	struct stm32_sai_sub_data *sai = mclk->sai_data;
	int div, ret;

	div = stm32_sai_get_clk_div(sai, parent_rate, rate);
	if (div < 0)
		return div;

	ret = stm32_sai_set_clk_div(sai, div);
	if (ret)
		return ret;

	mclk->freq = rate;

	return 0;
}