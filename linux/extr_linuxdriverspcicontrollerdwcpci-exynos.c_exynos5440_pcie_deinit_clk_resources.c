#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct exynos_pcie {TYPE_1__* clk_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  bus_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos5440_pcie_deinit_clk_resources(struct exynos_pcie *ep)
{
	clk_disable_unprepare(ep->clk_res->bus_clk);
	clk_disable_unprepare(ep->clk_res->clk);
}