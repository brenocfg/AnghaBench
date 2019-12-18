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
struct stm32_sai_mclk_data {unsigned long freq; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct stm32_sai_mclk_data* to_mclk_data (struct clk_hw*) ; 

__attribute__((used)) static unsigned long stm32_sai_mclk_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct stm32_sai_mclk_data *mclk = to_mclk_data(hw);

	return mclk->freq;
}