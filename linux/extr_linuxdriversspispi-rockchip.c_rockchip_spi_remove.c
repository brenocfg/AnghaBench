#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int dummy; } ;
struct TYPE_4__ {scalar_t__ ch; } ;
struct TYPE_3__ {scalar_t__ ch; } ;
struct rockchip_spi {TYPE_2__ dma_rx; TYPE_1__ dma_tx; int /*<<< orphan*/  apb_pclk; int /*<<< orphan*/  spiclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 struct spi_master* spi_master_get (int /*<<< orphan*/ ) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int rockchip_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = spi_master_get(platform_get_drvdata(pdev));
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	pm_runtime_get_sync(&pdev->dev);

	clk_disable_unprepare(rs->spiclk);
	clk_disable_unprepare(rs->apb_pclk);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);

	if (rs->dma_tx.ch)
		dma_release_channel(rs->dma_tx.ch);
	if (rs->dma_rx.ch)
		dma_release_channel(rs->dma_rx.ch);

	spi_master_put(master);

	return 0;
}