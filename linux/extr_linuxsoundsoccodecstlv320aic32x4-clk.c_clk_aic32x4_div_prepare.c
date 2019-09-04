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
 int /*<<< orphan*/  AIC32X4_DIVEN ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_aic32x4* to_clk_aic32x4 (struct clk_hw*) ; 

__attribute__((used)) static int clk_aic32x4_div_prepare(struct clk_hw *hw)
{
	struct clk_aic32x4 *div = to_clk_aic32x4(hw);

	return regmap_update_bits(div->regmap, div->reg,
				AIC32X4_DIVEN, AIC32X4_DIVEN);
}