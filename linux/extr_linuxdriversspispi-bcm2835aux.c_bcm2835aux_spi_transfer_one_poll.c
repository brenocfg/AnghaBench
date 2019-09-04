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
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct bcm2835aux_spi {scalar_t__ rx_len; scalar_t__ tx_len; int /*<<< orphan*/ * cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL0 ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 unsigned long BCM2835_AUX_SPI_POLLING_JIFFIES ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_STAT ; 
 int BCM2835_AUX_SPI_STAT_BUSY ; 
 int BCM2835_AUX_SPI_STAT_RX_EMPTY ; 
 int BCM2835_AUX_SPI_STAT_TX_FULL ; 
 int __bcm2835aux_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int bcm2835aux_rd (struct bcm2835aux_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835aux_rd_fifo (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835aux_wr_fifo (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*,unsigned long,scalar_t__,scalar_t__) ; 
 unsigned long jiffies ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int bcm2835aux_spi_transfer_one_poll(struct spi_master *master,
					    struct spi_device *spi,
					struct spi_transfer *tfr)
{
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);
	unsigned long timeout;
	u32 stat;

	/* configure spi */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	/* set the timeout */
	timeout = jiffies + BCM2835_AUX_SPI_POLLING_JIFFIES;

	/* loop until finished the transfer */
	while (bs->rx_len) {
		/* read status */
		stat = bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT);

		/* fill in tx fifo with remaining data */
		if ((bs->tx_len) && (!(stat & BCM2835_AUX_SPI_STAT_TX_FULL))) {
			bcm2835aux_wr_fifo(bs);
			continue;
		}

		/* read data from fifo for both cases */
		if (!(stat & BCM2835_AUX_SPI_STAT_RX_EMPTY)) {
			bcm2835aux_rd_fifo(bs);
			continue;
		}
		if (!(stat & BCM2835_AUX_SPI_STAT_BUSY)) {
			bcm2835aux_rd_fifo(bs);
			continue;
		}

		/* there is still data pending to read check the timeout */
		if (bs->rx_len && time_after(jiffies, timeout)) {
			dev_dbg_ratelimited(&spi->dev,
					    "timeout period reached: jiffies: %lu remaining tx/rx: %d/%d - falling back to interrupt mode\n",
					    jiffies - timeout,
					    bs->tx_len, bs->rx_len);
			/* forward to interrupt handler */
			return __bcm2835aux_spi_transfer_one_irq(master,
							       spi, tfr);
		}
	}

	/* and return without waiting for completion */
	return 0;
}