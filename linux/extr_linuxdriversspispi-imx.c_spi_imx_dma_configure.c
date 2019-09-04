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
struct spi_master {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct spi_imx_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  wml; scalar_t__ base_phys; int /*<<< orphan*/  bits_per_word; } ;
struct dma_slave_config {int dst_addr_width; int src_addr_width; int /*<<< orphan*/  src_maxburst; scalar_t__ src_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  dst_maxburst; scalar_t__ dst_addr; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 scalar_t__ MXC_CSPIRXDATA ; 
 scalar_t__ MXC_CSPITXDATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int spi_imx_bytes_per_word (int /*<<< orphan*/ ) ; 
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int spi_imx_dma_configure(struct spi_master *master)
{
	int ret;
	enum dma_slave_buswidth buswidth;
	struct dma_slave_config rx = {}, tx = {};
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);

	switch (spi_imx_bytes_per_word(spi_imx->bits_per_word)) {
	case 4:
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
		break;
	case 2:
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
		break;
	case 1:
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
		break;
	default:
		return -EINVAL;
	}

	tx.direction = DMA_MEM_TO_DEV;
	tx.dst_addr = spi_imx->base_phys + MXC_CSPITXDATA;
	tx.dst_addr_width = buswidth;
	tx.dst_maxburst = spi_imx->wml;
	ret = dmaengine_slave_config(master->dma_tx, &tx);
	if (ret) {
		dev_err(spi_imx->dev, "TX dma configuration failed with %d\n", ret);
		return ret;
	}

	rx.direction = DMA_DEV_TO_MEM;
	rx.src_addr = spi_imx->base_phys + MXC_CSPIRXDATA;
	rx.src_addr_width = buswidth;
	rx.src_maxburst = spi_imx->wml;
	ret = dmaengine_slave_config(master->dma_rx, &rx);
	if (ret) {
		dev_err(spi_imx->dev, "RX dma configuration failed with %d\n", ret);
		return ret;
	}

	return 0;
}