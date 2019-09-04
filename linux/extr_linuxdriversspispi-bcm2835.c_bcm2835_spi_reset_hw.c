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
struct spi_master {int dummy; } ;
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CLEAR_RX ; 
 int BCM2835_SPI_CS_CLEAR_TX ; 
 int BCM2835_SPI_CS_DMAEN ; 
 int BCM2835_SPI_CS_INTD ; 
 int BCM2835_SPI_CS_INTR ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_DLEN ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void bcm2835_spi_reset_hw(struct spi_master *master)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/* Disable SPI interrupts and transfer */
	cs &= ~(BCM2835_SPI_CS_INTR |
		BCM2835_SPI_CS_INTD |
		BCM2835_SPI_CS_DMAEN |
		BCM2835_SPI_CS_TA);
	/* and reset RX/TX FIFOS */
	cs |= BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX;

	/* and reset the SPI_HW */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);
	/* as well as DLEN */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, 0);
}