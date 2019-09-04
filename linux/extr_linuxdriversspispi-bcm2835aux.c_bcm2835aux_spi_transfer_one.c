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
struct spi_transfer {unsigned long speed_hz; unsigned long len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct bcm2835aux_spi {unsigned long* cntl; unsigned long tx_len; unsigned long rx_len; scalar_t__ pending; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long BCM2835_AUX_SPI_CNTL0_SPEED ; 
 unsigned long BCM2835_AUX_SPI_CNTL0_SPEED_MAX ; 
 unsigned long BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT ; 
 int BCM2835_AUX_SPI_POLLING_LIMIT_US ; 
 int DIV_ROUND_UP (unsigned long,int) ; 
 int bcm2835aux_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int bcm2835aux_spi_transfer_one_poll (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835aux_spi_transfer_one(struct spi_master *master,
				       struct spi_device *spi,
				       struct spi_transfer *tfr)
{
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);
	unsigned long spi_hz, clk_hz, speed;
	unsigned long spi_used_hz;

	/* calculate the registers to handle
	 *
	 * note that we use the variable data mode, which
	 * is not optimal for longer transfers as we waste registers
	 * resulting (potentially) in more interrupts when transferring
	 * more than 12 bytes
	 */

	/* set clock */
	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	if (spi_hz >= clk_hz / 2) {
		speed = 0;
	} else if (spi_hz) {
		speed = DIV_ROUND_UP(clk_hz, 2 * spi_hz) - 1;
		if (speed >  BCM2835_AUX_SPI_CNTL0_SPEED_MAX)
			speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
	} else { /* the slowest we can go */
		speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
	}
	/* mask out old speed from previous spi_transfer */
	bs->cntl[0] &= ~(BCM2835_AUX_SPI_CNTL0_SPEED);
	/* set the new speed */
	bs->cntl[0] |= speed << BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT;

	spi_used_hz = clk_hz / (2 * (speed + 1));

	/* set transmit buffers and length */
	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;
	bs->pending = 0;

	/* Calculate the estimated time in us the transfer runs.  Note that
	 * there are are 2 idle clocks cycles after each chunk getting
	 * transferred - in our case the chunk size is 3 bytes, so we
	 * approximate this by 9 cycles/byte.  This is used to find the number
	 * of Hz per byte per polling limit.  E.g., we can transfer 1 byte in
	 * 30 µs per 300,000 Hz of bus clock.
	 */
#define HZ_PER_BYTE ((9 * 1000000) / BCM2835_AUX_SPI_POLLING_LIMIT_US)
	/* run in polling mode for short transfers */
	if (tfr->len < spi_used_hz / HZ_PER_BYTE)
		return bcm2835aux_spi_transfer_one_poll(master, spi, tfr);

	/* run in interrupt mode for all others */
	return bcm2835aux_spi_transfer_one_irq(master, spi, tfr);
#undef HZ_PER_BYTE
}