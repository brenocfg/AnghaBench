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
struct bcm2835_spi {int /*<<< orphan*/  rx_len; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bcm2835_rd_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_master*) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static irqreturn_t bcm2835_spi_interrupt(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct bcm2835_spi *bs = spi_master_get_devdata(master);

	/* Read as many bytes as possible from FIFO */
	bcm2835_rd_fifo(bs);
	/* Write as many bytes as possible to FIFO */
	bcm2835_wr_fifo(bs);

	if (!bs->rx_len) {
		/* Transfer complete - reset SPI HW */
		bcm2835_spi_reset_hw(master);
		/* wake up the framework */
		complete(&master->xfer_completion);
	}

	return IRQ_HANDLED;
}