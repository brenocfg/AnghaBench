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
struct device {int dummy; } ;
struct ci_hdrc_imx_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_per; scalar_t__ need_three_clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ci_hdrc_imx_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int imx_prepare_enable_clks(struct device *dev)
{
	struct ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	int ret = 0;

	if (data->need_three_clks) {
		ret = clk_prepare_enable(data->clk_ipg);
		if (ret) {
			dev_err(dev,
				"Failed to prepare/enable ipg clk, err=%d\n",
				ret);
			return ret;
		}

		ret = clk_prepare_enable(data->clk_ahb);
		if (ret) {
			dev_err(dev,
				"Failed to prepare/enable ahb clk, err=%d\n",
				ret);
			clk_disable_unprepare(data->clk_ipg);
			return ret;
		}

		ret = clk_prepare_enable(data->clk_per);
		if (ret) {
			dev_err(dev,
				"Failed to prepare/enable per clk, err=%d\n",
				ret);
			clk_disable_unprepare(data->clk_ahb);
			clk_disable_unprepare(data->clk_ipg);
			return ret;
		}
	} else {
		ret = clk_prepare_enable(data->clk);
		if (ret) {
			dev_err(dev,
				"Failed to prepare/enable clk, err=%d\n",
				ret);
			return ret;
		}
	}

	return ret;
}