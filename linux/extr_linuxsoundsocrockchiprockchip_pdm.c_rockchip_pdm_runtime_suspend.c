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
struct rk_pdm_dev {int /*<<< orphan*/  hclk; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rk_pdm_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int rockchip_pdm_runtime_suspend(struct device *dev)
{
	struct rk_pdm_dev *pdm = dev_get_drvdata(dev);

	clk_disable_unprepare(pdm->clk);
	clk_disable_unprepare(pdm->hclk);

	return 0;
}