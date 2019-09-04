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
struct tegra_soctherm {int /*<<< orphan*/  debugfs_dir; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct tegra_soctherm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  soctherm_clk_enable (struct platform_device*,int) ; 

__attribute__((used)) static int tegra_soctherm_remove(struct platform_device *pdev)
{
	struct tegra_soctherm *tegra = platform_get_drvdata(pdev);

	debugfs_remove_recursive(tegra->debugfs_dir);

	soctherm_clk_enable(pdev, false);

	return 0;
}