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
struct spi_device {int /*<<< orphan*/  cs_gpio; } ;
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_INTD ; 
 int BCM2835_SPI_CS_INTR ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo (struct bcm2835_spi*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one_irq(struct spi_master *master,
					struct spi_device *spi,
					struct spi_transfer *tfr,
					u32 cs)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);

	/* fill in fifo if we have gpio-cs
	 * note that there have been rare events where the native-CS
	 * flapped for <1us which may change the behaviour
	 * with gpio-cs this does not happen, so it is implemented
	 * only for this case
	 */
	if (gpio_is_valid(spi->cs_gpio)) {
		/* enable HW block, but without interrupts enabled
		 * this would triggern an immediate interrupt
		 */
		bcm2835_wr(bs, BCM2835_SPI_CS,
			   cs | BCM2835_SPI_CS_TA);
		/* fill in tx fifo as much as possible */
		bcm2835_wr_fifo(bs);
	}

	/*
	 * Enable the HW block. This will immediately trigger a DONE (TX
	 * empty) interrupt, upon which we will fill the TX FIFO with the
	 * first TX bytes. Pre-filling the TX FIFO here to avoid the
	 * interrupt doesn't work:-(
	 */
	cs |= BCM2835_SPI_CS_INTR | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_TA;
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);

	/* signal that we need to wait for completion */
	return 1;
}