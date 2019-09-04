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
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mxs_ssp {int /*<<< orphan*/  dmach; } ;
struct mxs_spi {struct mxs_ssp ssp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_spi_runtime_suspend (int /*<<< orphan*/ *) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 struct mxs_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int mxs_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master;
	struct mxs_spi *spi;
	struct mxs_ssp *ssp;

	master = platform_get_drvdata(pdev);
	spi = spi_master_get_devdata(master);
	ssp = &spi->ssp;

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		mxs_spi_runtime_suspend(&pdev->dev);

	dma_release_channel(ssp->dmach);

	return 0;
}