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
typedef  int u8 ;
typedef  int u16 ;
struct spi_device {int chip_select; scalar_t__ cs_gpio; int mode; int /*<<< orphan*/  master; struct davinci_spi_config* controller_data; } ;
struct davinci_spi_platform_data {int dummy; } ;
struct davinci_spi_config {scalar_t__ wdelay; } ;
struct davinci_spi {scalar_t__ base; struct davinci_spi_platform_data pdata; } ;

/* Variables and functions */
 int BITBANG_CS_ACTIVE ; 
 int CS_DEFAULT ; 
 scalar_t__ SPIDAT1 ; 
 int SPIDAT1_CSHOLD_MASK ; 
 int SPIDAT1_WDEL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 struct davinci_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void davinci_spi_chipselect(struct spi_device *spi, int value)
{
	struct davinci_spi *dspi;
	struct davinci_spi_platform_data *pdata;
	struct davinci_spi_config *spicfg = spi->controller_data;
	u8 chip_sel = spi->chip_select;
	u16 spidat1 = CS_DEFAULT;

	dspi = spi_master_get_devdata(spi->master);
	pdata = &dspi->pdata;

	/* program delay transfers if tx_delay is non zero */
	if (spicfg && spicfg->wdelay)
		spidat1 |= SPIDAT1_WDEL;

	/*
	 * Board specific chip select logic decides the polarity and cs
	 * line for the controller
	 */
	if (spi->cs_gpio >= 0) {
		if (value == BITBANG_CS_ACTIVE)
			gpio_set_value(spi->cs_gpio, spi->mode & SPI_CS_HIGH);
		else
			gpio_set_value(spi->cs_gpio,
				!(spi->mode & SPI_CS_HIGH));
	} else {
		if (value == BITBANG_CS_ACTIVE) {
			spidat1 |= SPIDAT1_CSHOLD_MASK;
			spidat1 &= ~(0x1 << chip_sel);
		}
	}

	iowrite16(spidat1, dspi->base + SPIDAT1 + 2);
}