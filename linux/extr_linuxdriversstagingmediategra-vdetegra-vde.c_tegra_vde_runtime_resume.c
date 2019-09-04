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
struct tegra_vde {int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_VDEC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_vde* dev_get_drvdata (struct device*) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_vde_runtime_resume(struct device *dev)
{
	struct tegra_vde *vde = dev_get_drvdata(dev);
	int err;

	err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_VDEC,
						vde->clk, vde->rst);
	if (err) {
		dev_err(dev, "Failed to power up HW : %d\n", err);
		return err;
	}

	return 0;
}