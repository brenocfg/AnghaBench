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
struct spi_master {int /*<<< orphan*/  xfer_completion; } ;
struct bcm2835aux_spi {int pending; int* cntl; scalar_t__ rx_len; scalar_t__ tx_len; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 int BCM2835_AUX_SPI_CNTL1_IDLE ; 
 int BCM2835_AUX_SPI_CNTL1_TXEMPTY ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_STAT ; 
 int BCM2835_AUX_SPI_STAT_BUSY ; 
 int BCM2835_AUX_SPI_STAT_RX_EMPTY ; 
 int BCM2835_AUX_SPI_STAT_TX_FULL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int bcm2835aux_rd (struct bcm2835aux_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835aux_rd_fifo (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835aux_wr_fifo (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static irqreturn_t bcm2835aux_spi_interrupt(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);
	irqreturn_t ret = IRQ_NONE;

	/* IRQ may be shared, so return if our interrupts are disabled */
	if (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_CNTL1) &
	      (BCM2835_AUX_SPI_CNTL1_TXEMPTY | BCM2835_AUX_SPI_CNTL1_IDLE)))
		return ret;

	/* check if we have data to read */
	while (bs->rx_len &&
	       (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_RX_EMPTY))) {
		bcm2835aux_rd_fifo(bs);
		ret = IRQ_HANDLED;
	}

	/* check if we have data to write */
	while (bs->tx_len &&
	       (bs->pending < 12) &&
	       (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_TX_FULL))) {
		bcm2835aux_wr_fifo(bs);
		ret = IRQ_HANDLED;
	}

	/* and check if we have reached "done" */
	while (bs->rx_len &&
	       (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_BUSY))) {
		bcm2835aux_rd_fifo(bs);
		ret = IRQ_HANDLED;
	}

	if (!bs->tx_len) {
		/* disable tx fifo empty interrupt */
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] |
			BCM2835_AUX_SPI_CNTL1_IDLE);
	}

	/* and if rx_len is 0 then disable interrupts and wake up completion */
	if (!bs->rx_len) {
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
		complete(&master->xfer_completion);
	}

	/* and return */
	return ret;
}