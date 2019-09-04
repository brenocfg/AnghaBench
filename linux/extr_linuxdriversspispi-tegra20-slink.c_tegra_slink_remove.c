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
struct tegra_slink_data {scalar_t__ rx_dma_chan; scalar_t__ tx_dma_chan; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; } ;
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_slink_data*) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 struct tegra_slink_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  tegra_slink_deinit_dma_param (struct tegra_slink_data*,int) ; 
 int /*<<< orphan*/  tegra_slink_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_slink_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct tegra_slink_data	*tspi = spi_master_get_devdata(master);

	free_irq(tspi->irq, tspi);

	clk_disable(tspi->clk);

	if (tspi->tx_dma_chan)
		tegra_slink_deinit_dma_param(tspi, false);

	if (tspi->rx_dma_chan)
		tegra_slink_deinit_dma_param(tspi, true);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_slink_runtime_suspend(&pdev->dev);

	return 0;
}