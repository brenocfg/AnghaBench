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
struct tegra_xusb {int /*<<< orphan*/  supplies; TYPE_1__* soc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_supplies; } ;

/* Variables and functions */
 struct tegra_xusb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_xusb_clk_disable (struct tegra_xusb*) ; 
 int /*<<< orphan*/  tegra_xusb_phy_disable (struct tegra_xusb*) ; 

__attribute__((used)) static int tegra_xusb_runtime_suspend(struct device *dev)
{
	struct tegra_xusb *tegra = dev_get_drvdata(dev);

	tegra_xusb_phy_disable(tegra);
	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);
	tegra_xusb_clk_disable(tegra);

	return 0;
}