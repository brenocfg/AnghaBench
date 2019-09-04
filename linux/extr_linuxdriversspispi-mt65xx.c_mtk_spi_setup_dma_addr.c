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
struct spi_transfer {int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; } ;
struct spi_master {int dummy; } ;
struct mtk_spi {scalar_t__ base; scalar_t__ rx_sgl; scalar_t__ tx_sgl; } ;

/* Variables and functions */
 scalar_t__ SPI_RX_DST_REG ; 
 scalar_t__ SPI_TX_SRC_REG ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_spi_setup_dma_addr(struct spi_master *master,
				   struct spi_transfer *xfer)
{
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	if (mdata->tx_sgl)
		writel(xfer->tx_dma, mdata->base + SPI_TX_SRC_REG);
	if (mdata->rx_sgl)
		writel(xfer->rx_dma, mdata->base + SPI_RX_DST_REG);
}