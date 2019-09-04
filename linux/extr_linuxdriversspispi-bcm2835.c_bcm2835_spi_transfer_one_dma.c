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
typedef  int u32 ;
struct spi_transfer {int len; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/  tx_sg; } ;
struct spi_master {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct bcm2835_spi {int dma_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_DMAEN ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_DLEN ; 
 scalar_t__ bcm2835_check_sg_length (int /*<<< orphan*/ *) ; 
 int bcm2835_spi_prepare_sg (struct spi_master*,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_master*) ; 
 int bcm2835_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one_dma(struct spi_master *master,
					struct spi_device *spi,
					struct spi_transfer *tfr,
					u32 cs)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	int ret;

	/* check that the scatter gather segments are all a multiple of 4 */
	if (bcm2835_check_sg_length(&tfr->tx_sg) ||
	    bcm2835_check_sg_length(&tfr->rx_sg)) {
		dev_warn_once(&spi->dev,
			      "scatter gather segment length is not a multiple of 4 - falling back to interrupt mode\n");
		return bcm2835_spi_transfer_one_irq(master, spi, tfr, cs);
	}

	/* setup tx-DMA */
	ret = bcm2835_spi_prepare_sg(master, tfr, true);
	if (ret)
		return ret;

	/* start TX early */
	dma_async_issue_pending(master->dma_tx);

	/* mark as dma pending */
	bs->dma_pending = 1;

	/* set the DMA length */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, tfr->len);

	/* start the HW */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   cs | BCM2835_SPI_CS_TA | BCM2835_SPI_CS_DMAEN);

	/* setup rx-DMA late - to run transfers while
	 * mapping of the rx buffers still takes place
	 * this saves 10us or more.
	 */
	ret = bcm2835_spi_prepare_sg(master, tfr, false);
	if (ret) {
		/* need to reset on errors */
		dmaengine_terminate_all(master->dma_tx);
		bs->dma_pending = false;
		bcm2835_spi_reset_hw(master);
		return ret;
	}

	/* start rx dma late */
	dma_async_issue_pending(master->dma_rx);

	/* wait for wakeup in framework */
	return 1;
}