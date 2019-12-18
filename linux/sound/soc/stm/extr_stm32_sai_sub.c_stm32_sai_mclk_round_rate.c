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
 struct stm32_sai_mclk_data* to_mclk_data (struct clk_hw*) ; 

__attribute__((used)) static long stm32_sai_mclk_round_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long *prate)
{
	struct stm32_sai_mclk_data *mclk = to_mclk_data(hw);
	struct stm32_sai_sub_data *sai = mclk->sai_data;
	int div;

	div = stm32_sai_get_clk_div(sai, *prate, rate);
	if (div < 0)
		return div;

	mclk->freq = *prate / div;

	return mclk->freq;
}