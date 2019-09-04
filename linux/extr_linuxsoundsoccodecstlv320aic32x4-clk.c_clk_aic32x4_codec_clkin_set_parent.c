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
struct clk_aic32x4 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_CLKMUX ; 
 int /*<<< orphan*/  AIC32X4_CODEC_CLKIN_MASK ; 
 int AIC32X4_CODEC_CLKIN_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct clk_aic32x4* to_clk_aic32x4 (struct clk_hw*) ; 

__attribute__((used)) static int clk_aic32x4_codec_clkin_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_aic32x4 *mux = to_clk_aic32x4(hw);

	return regmap_update_bits(mux->regmap,
		AIC32X4_CLKMUX,
		AIC32X4_CODEC_CLKIN_MASK, index << AIC32X4_CODEC_CLKIN_SHIFT);
}