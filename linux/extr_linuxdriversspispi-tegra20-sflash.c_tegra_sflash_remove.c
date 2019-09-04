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
struct tegra_sflash_data {int /*<<< orphan*/  irq; } ;
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_sflash_data*) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 struct tegra_sflash_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  tegra_sflash_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_sflash_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct tegra_sflash_data	*tsd = spi_master_get_devdata(master);

	free_irq(tsd->irq, tsd);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_sflash_runtime_suspend(&pdev->dev);

	return 0;
}