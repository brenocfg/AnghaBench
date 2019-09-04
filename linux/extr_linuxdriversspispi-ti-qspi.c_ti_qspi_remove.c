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
struct ti_qspi {scalar_t__ rx_chan; int /*<<< orphan*/  rx_bb_dma_addr; scalar_t__ rx_bb_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct ti_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int spi_master_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_qspi_remove(struct platform_device *pdev)
{
	struct ti_qspi *qspi = platform_get_drvdata(pdev);
	int rc;

	rc = spi_master_suspend(qspi->master);
	if (rc)
		return rc;

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	if (qspi->rx_bb_addr)
		dma_free_coherent(qspi->dev, QSPI_DMA_BUFFER_SIZE,
				  qspi->rx_bb_addr,
				  qspi->rx_bb_dma_addr);
	if (qspi->rx_chan)
		dma_release_channel(qspi->rx_chan);

	return 0;
}