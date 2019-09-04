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
 struct ci_hdrc_imx_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void imx_disable_unprepare_clks(struct device *dev)
{
	struct ci_hdrc_imx_data *data = dev_get_drvdata(dev);

	if (data->need_three_clks) {
		clk_disable_unprepare(data->clk_per);
		clk_disable_unprepare(data->clk_ahb);
		clk_disable_unprepare(data->clk_ipg);
	} else {
		clk_disable_unprepare(data->clk);
	}
}