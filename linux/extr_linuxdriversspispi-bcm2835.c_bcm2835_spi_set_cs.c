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
struct spi_device {int mode; int chip_select; struct spi_master* master; } ;
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CSPOL ; 
 int BCM2835_SPI_CS_CSPOL0 ; 
 int BCM2835_SPI_CS_CS_01 ; 
 int BCM2835_SPI_CS_CS_10 ; 
 int SPI_CS_HIGH ; 
 int SPI_NO_CS ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void bcm2835_spi_set_cs(struct spi_device *spi, bool gpio_level)
{
	/*
	 * we can assume that we are "native" as per spi_set_cs
	 *   calling us ONLY when cs_gpio is not set
	 * we can also assume that we are CS < 3 as per bcm2835_spi_setup
	 *   we would not get called because of error handling there.
	 * the level passed is the electrical level not enabled/disabled
	 *   so it has to get translated back to enable/disable
	 *   see spi_set_cs in spi.c for the implementation
	 */

	struct spi_master *master = spi->master;
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);
	bool enable;

	/* calculate the enable flag from the passed gpio_level */
	enable = (spi->mode & SPI_CS_HIGH) ? gpio_level : !gpio_level;

	/* set flags for "reverse" polarity in the registers */
	if (spi->mode & SPI_CS_HIGH) {
		/* set the correct CS-bits */
		cs |= BCM2835_SPI_CS_CSPOL;
		cs |= BCM2835_SPI_CS_CSPOL0 << spi->chip_select;
	} else {
		/* clean the CS-bits */
		cs &= ~BCM2835_SPI_CS_CSPOL;
		cs &= ~(BCM2835_SPI_CS_CSPOL0 << spi->chip_select);
	}

	/* select the correct chip_select depending on disabled/enabled */
	if (enable) {
		/* set cs correctly */
		if (spi->mode & SPI_NO_CS) {
			/* use the "undefined" chip-select */
			cs |= BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;
		} else {
			/* set the chip select */
			cs &= ~(BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01);
			cs |= spi->chip_select;
		}
	} else {
		/* disable CSPOL which puts HW-CS into deselected state */
		cs &= ~BCM2835_SPI_CS_CSPOL;
		/* use the "undefined" chip-select as precaution */
		cs |= BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;
	}

	/* finally set the calculated flags in SPI_CS */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);
}