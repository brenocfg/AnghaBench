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
struct wcd9335_codec {scalar_t__ clk_mclk_users; scalar_t__ clk_rco_users; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_EXT_CLKBUF_DISABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_DISABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_SRC_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_SRC_RCO ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_TOP ; 
 int /*<<< orphan*/  WCD_CLK_OFF ; 
 int /*<<< orphan*/  WCD_CLK_RCO ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcd9335_disable_mclk(struct wcd9335_codec *wcd)
{
	if (wcd->clk_mclk_users <= 0)
		return -EINVAL;

	if (--wcd->clk_mclk_users == 0) {
		if (wcd->clk_rco_users > 0) {
			/* MCLK to RCO switch */
			regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_SRC_MASK,
					WCD9335_ANA_CLK_MCLK_SRC_RCO);
			wcd->clk_type = WCD_CLK_RCO;
		} else {
			regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_EN_MASK,
					WCD9335_ANA_CLK_MCLK_DISABLE);
			wcd->clk_type = WCD_CLK_OFF;
		}

		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK,
					WCD9335_ANA_CLK_EXT_CLKBUF_DISABLE);
	}

	return 0;
}