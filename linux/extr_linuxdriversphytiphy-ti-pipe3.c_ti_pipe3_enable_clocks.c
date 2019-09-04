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
struct ti_pipe3 {int /*<<< orphan*/  refclk; int /*<<< orphan*/  wkupclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  div_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ti_pipe3_enable_clocks(struct ti_pipe3 *phy)
{
	int ret = 0;

	if (!IS_ERR(phy->refclk)) {
		ret = clk_prepare_enable(phy->refclk);
		if (ret) {
			dev_err(phy->dev, "Failed to enable refclk %d\n", ret);
			return ret;
		}
	}

	if (!IS_ERR(phy->wkupclk)) {
		ret = clk_prepare_enable(phy->wkupclk);
		if (ret) {
			dev_err(phy->dev, "Failed to enable wkupclk %d\n", ret);
			goto disable_refclk;
		}
	}

	if (!IS_ERR(phy->div_clk)) {
		ret = clk_prepare_enable(phy->div_clk);
		if (ret) {
			dev_err(phy->dev, "Failed to enable div_clk %d\n", ret);
			goto disable_wkupclk;
		}
	}

	return 0;

disable_wkupclk:
	if (!IS_ERR(phy->wkupclk))
		clk_disable_unprepare(phy->wkupclk);

disable_refclk:
	if (!IS_ERR(phy->refclk))
		clk_disable_unprepare(phy->refclk);

	return ret;
}