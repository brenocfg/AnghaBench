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
struct wcd9335_codec {scalar_t__ master_bias_users; int clk_mclk_users; scalar_t__ clk_type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_EXT_CLKBUF_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_SRC_EXTERNAL ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_MCLK_SRC_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_CLK_TOP ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_FS_CNT_CONTROL ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_FS_CNT_ENABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_FS_CNT_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_MCLK_CONTROL ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_MCLK_ENABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_CLK_RST_CTRL_MCLK_EN_MASK ; 
 scalar_t__ WCD_CLK_MCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wcd9335_enable_mclk(struct wcd9335_codec *wcd)
{
	/* Enable mclk requires master bias to be enabled first */
	if (wcd->master_bias_users <= 0)
		return -EINVAL;

	if (((wcd->clk_mclk_users == 0) && (wcd->clk_type == WCD_CLK_MCLK)) ||
	    ((wcd->clk_mclk_users > 0) && (wcd->clk_type != WCD_CLK_MCLK))) {
		dev_err(wcd->dev, "Error enabling MCLK, clk_type: %d\n",
			wcd->clk_type);
		return -EINVAL;
	}

	if (++wcd->clk_mclk_users == 1) {
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_EXT_CLKBUF_EN_MASK,
					WCD9335_ANA_CLK_EXT_CLKBUF_ENABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_SRC_MASK,
					WCD9335_ANA_CLK_MCLK_SRC_EXTERNAL);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_CLK_TOP,
					WCD9335_ANA_CLK_MCLK_EN_MASK,
					WCD9335_ANA_CLK_MCLK_ENABLE);
		regmap_update_bits(wcd->regmap,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_CONTROL,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_EN_MASK,
				   WCD9335_CDC_CLK_RST_CTRL_FS_CNT_ENABLE);
		regmap_update_bits(wcd->regmap,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_CONTROL,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_EN_MASK,
				   WCD9335_CDC_CLK_RST_CTRL_MCLK_ENABLE);
		/*
		 * 10us sleep is required after clock is enabled
		 * as per HW requirement
		 */
		usleep_range(10, 15);
	}

	wcd->clk_type = WCD_CLK_MCLK;

	return 0;
}