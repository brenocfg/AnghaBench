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
struct rk_pdm_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  hclk; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rk_pdm_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int rockchip_pdm_runtime_resume(struct device *dev)
{
	struct rk_pdm_dev *pdm = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(pdm->clk);
	if (ret) {
		dev_err(pdm->dev, "clock enable failed %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(pdm->hclk);
	if (ret) {
		dev_err(pdm->dev, "hclock enable failed %d\n", ret);
		return ret;
	}

	return 0;
}