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
struct spi_master {int /*<<< orphan*/  dev; } ;
struct ep93xx_spi {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;
struct dma_async_tx_descriptor {struct spi_master* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR (struct dma_async_tx_descriptor*) ; 
 int PTR_ERR (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  ep93xx_spi_dma_callback ; 
 int /*<<< orphan*/  ep93xx_spi_dma_finish (struct spi_master*,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* ep93xx_spi_dma_prepare (struct spi_master*,int /*<<< orphan*/ ) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int ep93xx_spi_dma_transfer(struct spi_master *master)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	struct dma_async_tx_descriptor *rxd, *txd;

	rxd = ep93xx_spi_dma_prepare(master, DMA_FROM_DEVICE);
	if (IS_ERR(rxd)) {
		dev_err(&master->dev, "DMA RX failed: %ld\n", PTR_ERR(rxd));
		return PTR_ERR(rxd);
	}

	txd = ep93xx_spi_dma_prepare(master, DMA_TO_DEVICE);
	if (IS_ERR(txd)) {
		ep93xx_spi_dma_finish(master, DMA_FROM_DEVICE);
		dev_err(&master->dev, "DMA TX failed: %ld\n", PTR_ERR(txd));
		return PTR_ERR(txd);
	}

	/* We are ready when RX is done */
	rxd->callback = ep93xx_spi_dma_callback;
	rxd->callback_param = master;

	/* Now submit both descriptors and start DMA */
	dmaengine_submit(rxd);
	dmaengine_submit(txd);

	dma_async_issue_pending(espi->dma_rx);
	dma_async_issue_pending(espi->dma_tx);

	/* signal that we need to wait for completion */
	return 1;
}