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
struct spi_device {int mode; int chip_select; } ;
struct cns3xxx_spi {int dummy; } ;

/* Variables and functions */
#define  BITBANG_CS_ACTIVE 129 
#define  BITBANG_CS_INACTIVE 128 
 unsigned int SPI_CONFIGURATION_REG ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_TRANSMIT_CONTROL_REG ; 
 struct cns3xxx_spi* to_hw (struct spi_device*) ; 

__attribute__((used)) static void cns3xxx_spi_chipselect(struct spi_device *spi, int value)
{
	struct cns3xxx_spi *hw = to_hw(spi);
	unsigned int spi_config;

	switch (value) {
	case BITBANG_CS_INACTIVE:
		break;

	case BITBANG_CS_ACTIVE:
		spi_config = SPI_CONFIGURATION_REG;

		if (spi->mode & SPI_CPHA)
			spi_config |= (0x1 << 13);
		else
			spi_config &= ~(0x1 << 13);

		if (spi->mode & SPI_CPOL)
			spi_config |= (0x1 << 14);
		else
			spi_config &= ~(0x1 << 14);

		/* write new configration */
		SPI_CONFIGURATION_REG = spi_config;

		SPI_TRANSMIT_CONTROL_REG &= ~(0x7);
		SPI_TRANSMIT_CONTROL_REG |= (spi->chip_select & 0x3);

		break;
	}
}