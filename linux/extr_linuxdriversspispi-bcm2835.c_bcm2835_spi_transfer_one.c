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
struct spi_transfer {unsigned long speed_hz; scalar_t__ len; scalar_t__ rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_master {scalar_t__ can_dma; } ;
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; } ;
struct bcm2835_spi {scalar_t__ rx_len; scalar_t__ tx_len; scalar_t__ rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CLK ; 
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CS_01 ; 
 int BCM2835_SPI_CS_CS_10 ; 
 int BCM2835_SPI_CS_REN ; 
 unsigned long long BCM2835_SPI_POLLING_LIMIT_US ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int SPI_3WIRE ; 
 int SPI_NO_CS ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcm2835_spi_can_dma (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int bcm2835_spi_transfer_one_dma (struct spi_master*,struct spi_device*,struct spi_transfer*,int) ; 
 int bcm2835_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*,int) ; 
 int bcm2835_spi_transfer_one_poll (struct spi_master*,struct spi_device*,struct spi_transfer*,int,unsigned long long) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one(struct spi_master *master,
				    struct spi_device *spi,
				    struct spi_transfer *tfr)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	unsigned long spi_hz, clk_hz, cdiv;
	unsigned long spi_used_hz;
	unsigned long long xfer_time_us;
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/* set clock */
	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	if (spi_hz >= clk_hz / 2) {
		cdiv = 2; /* clk_hz/2 is the fastest we can go */
	} else if (spi_hz) {
		/* CDIV must be a multiple of two */
		cdiv = DIV_ROUND_UP(clk_hz, spi_hz);
		cdiv += (cdiv % 2);

		if (cdiv >= 65536)
			cdiv = 0; /* 0 is the slowest we can go */
	} else {
		cdiv = 0; /* 0 is the slowest we can go */
	}
	spi_used_hz = cdiv ? (clk_hz / cdiv) : (clk_hz / 65536);
	bcm2835_wr(bs, BCM2835_SPI_CLK, cdiv);

	/* handle all the 3-wire mode */
	if ((spi->mode & SPI_3WIRE) && (tfr->rx_buf))
		cs |= BCM2835_SPI_CS_REN;
	else
		cs &= ~BCM2835_SPI_CS_REN;

	/* for gpio_cs set dummy CS so that no HW-CS get changed
	 * we can not run this in bcm2835_spi_set_cs, as it does
	 * not get called for cs_gpio cases, so we need to do it here
	 */
	if (gpio_is_valid(spi->cs_gpio) || (spi->mode & SPI_NO_CS))
		cs |= BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;

	/* set transmit buffers and length */
	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;

	/* calculate the estimated time in us the transfer runs */
	xfer_time_us = (unsigned long long)tfr->len
		* 9 /* clocks/byte - SPI-HW waits 1 clock after each byte */
		* 1000000;
	do_div(xfer_time_us, spi_used_hz);

	/* for short requests run polling*/
	if (xfer_time_us <= BCM2835_SPI_POLLING_LIMIT_US)
		return bcm2835_spi_transfer_one_poll(master, spi, tfr,
						     cs, xfer_time_us);

	/* run in dma mode if conditions are right */
	if (master->can_dma && bcm2835_spi_can_dma(master, spi, tfr))
		return bcm2835_spi_transfer_one_dma(master, spi, tfr, cs);

	/* run in interrupt-mode */
	return bcm2835_spi_transfer_one_irq(master, spi, tfr, cs);
}