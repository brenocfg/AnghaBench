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
typedef  int u8 ;
struct clk_hw {int dummy; } ;
struct clk_aic32x4 {int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_DIV_MASK ; 
 int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct clk_aic32x4* to_clk_aic32x4 (struct clk_hw*) ; 

__attribute__((used)) static int clk_aic32x4_div_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct clk_aic32x4 *div = to_clk_aic32x4(hw);
	u8 divisor;

	divisor = DIV_ROUND_UP(parent_rate, rate);
	if (divisor > 128)
		return -EINVAL;

	return regmap_update_bits(div->regmap, div->reg,
				AIC32X4_DIV_MASK, divisor);
}