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
typedef  int /*<<< orphan*/  u32 ;
struct spi_device {int mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  cs_gpio; } ;
struct ath79_spi {int /*<<< orphan*/  ioc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_IOC_CLK ; 
 int /*<<< orphan*/  AR71XX_SPI_IOC_CS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_IOC ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  ath79_spi_wr (struct ath79_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath79_spi* ath79_spidev_to_sp (struct spi_device*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath79_spi_chipselect(struct spi_device *spi, int is_active)
{
	struct ath79_spi *sp = ath79_spidev_to_sp(spi);
	int cs_high = (spi->mode & SPI_CS_HIGH) ? is_active : !is_active;

	if (is_active) {
		/* set initial clock polarity */
		if (spi->mode & SPI_CPOL)
			sp->ioc_base |= AR71XX_SPI_IOC_CLK;
		else
			sp->ioc_base &= ~AR71XX_SPI_IOC_CLK;

		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, sp->ioc_base);
	}

	if (gpio_is_valid(spi->cs_gpio)) {
		/* SPI is normally active-low */
		gpio_set_value_cansleep(spi->cs_gpio, cs_high);
	} else {
		u32 cs_bit = AR71XX_SPI_IOC_CS(spi->chip_select);

		if (cs_high)
			sp->ioc_base |= cs_bit;
		else
			sp->ioc_base &= ~cs_bit;

		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, sp->ioc_base);
	}

}