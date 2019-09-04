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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra20_pinctrl ; 
 int /*<<< orphan*/  tegra20_pinctrl_register_clock_muxes (struct platform_device*) ; 
 int tegra_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra20_pinctrl_probe(struct platform_device *pdev)
{
	int err;

	err = tegra_pinctrl_probe(pdev, &tegra20_pinctrl);
	if (err)
		return err;

	tegra20_pinctrl_register_clock_muxes(pdev);

	return 0;
}