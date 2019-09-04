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
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_xusb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_xusb_clk_disable (struct tegra_xusb*) ; 
 int tegra_xusb_clk_enable (struct tegra_xusb*) ; 
 int tegra_xusb_phy_enable (struct tegra_xusb*) ; 

__attribute__((used)) static int tegra_xusb_runtime_resume(struct device *dev)
{
	struct tegra_xusb *tegra = dev_get_drvdata(dev);
	int err;

	err = tegra_xusb_clk_enable(tegra);
	if (err) {
		dev_err(dev, "failed to enable clocks: %d\n", err);
		return err;
	}

	err = regulator_bulk_enable(tegra->soc->num_supplies, tegra->supplies);
	if (err) {
		dev_err(dev, "failed to enable regulators: %d\n", err);
		goto disable_clk;
	}

	err = tegra_xusb_phy_enable(tegra);
	if (err < 0) {
		dev_err(dev, "failed to enable PHYs: %d\n", err);
		goto disable_regulator;
	}

	return 0;

disable_regulator:
	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);
disable_clk:
	tegra_xusb_clk_disable(tegra);
	return err;
}