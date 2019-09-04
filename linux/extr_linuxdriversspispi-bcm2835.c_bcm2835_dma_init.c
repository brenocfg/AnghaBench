#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int max_dma_len; int flags; int /*<<< orphan*/  can_dma; void* dma_rx; void* dma_tx; TYPE_1__ dev; } ;
struct dma_slave_config {void* src_addr_width; void* src_addr; int /*<<< orphan*/  direction; void* dst_addr_width; void* dst_addr; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ BCM2835_SPI_FIFO ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int SPI_MASTER_MUST_RX ; 
 int SPI_MASTER_MUST_TX ; 
 int /*<<< orphan*/  bcm2835_dma_release (struct spi_master*) ; 
 int /*<<< orphan*/  bcm2835_spi_can_dma ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dma_request_slave_channel (struct device*,char*) ; 
 int dmaengine_slave_config (void*,struct dma_slave_config*) ; 
 int /*<<< orphan*/ * of_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_dma_init(struct spi_master *master, struct device *dev)
{
	struct dma_slave_config slave_config;
	const __be32 *addr;
	dma_addr_t dma_reg_base;
	int ret;

	/* base address in dma-space */
	addr = of_get_address(master->dev.of_node, 0, NULL, NULL);
	if (!addr) {
		dev_err(dev, "could not get DMA-register address - not using dma mode\n");
		goto err;
	}
	dma_reg_base = be32_to_cpup(addr);

	/* get tx/rx dma */
	master->dma_tx = dma_request_slave_channel(dev, "tx");
	if (!master->dma_tx) {
		dev_err(dev, "no tx-dma configuration found - not using dma mode\n");
		goto err;
	}
	master->dma_rx = dma_request_slave_channel(dev, "rx");
	if (!master->dma_rx) {
		dev_err(dev, "no rx-dma configuration found - not using dma mode\n");
		goto err_release;
	}

	/* configure DMAs */
	slave_config.direction = DMA_MEM_TO_DEV;
	slave_config.dst_addr = (u32)(dma_reg_base + BCM2835_SPI_FIFO);
	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	ret = dmaengine_slave_config(master->dma_tx, &slave_config);
	if (ret)
		goto err_config;

	slave_config.direction = DMA_DEV_TO_MEM;
	slave_config.src_addr = (u32)(dma_reg_base + BCM2835_SPI_FIFO);
	slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	ret = dmaengine_slave_config(master->dma_rx, &slave_config);
	if (ret)
		goto err_config;

	/* all went well, so set can_dma */
	master->can_dma = bcm2835_spi_can_dma;
	master->max_dma_len = 65535; /* limitation by BCM2835_SPI_DLEN */
	/* need to do TX AND RX DMA, so we need dummy buffers */
	master->flags = SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX;

	return;

err_config:
	dev_err(dev, "issue configuring dma: %d - not using DMA mode\n",
		ret);
err_release:
	bcm2835_dma_release(master);
err:
	return;
}