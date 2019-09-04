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
struct rockchip_pcie {int /*<<< orphan*/  aclk_pcie; int /*<<< orphan*/  aclk_perf_pcie; int /*<<< orphan*/  hclk_pcie; int /*<<< orphan*/  clk_pcie_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

void rockchip_pcie_disable_clocks(void *data)
{
	struct rockchip_pcie *rockchip = data;

	clk_disable_unprepare(rockchip->clk_pcie_pm);
	clk_disable_unprepare(rockchip->hclk_pcie);
	clk_disable_unprepare(rockchip->aclk_perf_pcie);
	clk_disable_unprepare(rockchip->aclk_pcie);
}