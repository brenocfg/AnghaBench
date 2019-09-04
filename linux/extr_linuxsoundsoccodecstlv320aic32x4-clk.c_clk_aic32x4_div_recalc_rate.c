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
struct clk_aic32x4 {int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int AIC32X4_DIV_MASK ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_aic32x4* to_clk_aic32x4 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_aic32x4_div_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_aic32x4 *div = to_clk_aic32x4(hw);

	unsigned int val;

	regmap_read(div->regmap, div->reg, &val);

	return DIV_ROUND_UP(parent_rate, val & AIC32X4_DIV_MASK);
}