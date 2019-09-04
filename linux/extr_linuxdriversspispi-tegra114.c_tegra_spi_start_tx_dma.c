#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_spi_data {int /*<<< orphan*/  tx_dma_chan; TYPE_1__* tx_dma_desc; int /*<<< orphan*/  tx_dma_complete; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_dma_phys; } ;
struct TYPE_3__ {int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_1__*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_spi_dma_complete ; 

__attribute__((used)) static int tegra_spi_start_tx_dma(struct tegra_spi_data *tspi, int len)
{
	reinit_completion(&tspi->tx_dma_complete);
	tspi->tx_dma_desc = dmaengine_prep_slave_single(tspi->tx_dma_chan,
				tspi->tx_dma_phys, len, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);
	if (!tspi->tx_dma_desc) {
		dev_err(tspi->dev, "Not able to get desc for Tx\n");
		return -EIO;
	}

	tspi->tx_dma_desc->callback = tegra_spi_dma_complete;
	tspi->tx_dma_desc->callback_param = &tspi->tx_dma_complete;

	dmaengine_submit(tspi->tx_dma_desc);
	dma_async_issue_pending(tspi->tx_dma_chan);
	return 0;
}