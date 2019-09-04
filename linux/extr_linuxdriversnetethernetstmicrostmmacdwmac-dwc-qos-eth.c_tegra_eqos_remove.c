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
struct tegra_eqos {int /*<<< orphan*/  clk_master; int /*<<< orphan*/  clk_slave; int /*<<< orphan*/  clk_rx; int /*<<< orphan*/  clk_tx; int /*<<< orphan*/  reset; int /*<<< orphan*/  rst; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tegra_eqos* get_stmmac_bsp_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_eqos_remove(struct platform_device *pdev)
{
	struct tegra_eqos *eqos = get_stmmac_bsp_priv(&pdev->dev);

	reset_control_assert(eqos->rst);
	gpiod_set_value(eqos->reset, 1);
	clk_disable_unprepare(eqos->clk_tx);
	clk_disable_unprepare(eqos->clk_rx);
	clk_disable_unprepare(eqos->clk_slave);
	clk_disable_unprepare(eqos->clk_master);

	return 0;
}