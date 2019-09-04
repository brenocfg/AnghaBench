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
struct spi_device {int mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  dev; int /*<<< orphan*/  cs_gpio; } ;
struct ath79_spi {int /*<<< orphan*/  ioc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_IOC_CS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_IOC ; 
 unsigned long GPIOF_DIR_OUT ; 
 unsigned long GPIOF_INIT_HIGH ; 
 unsigned long GPIOF_INIT_LOW ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  ath79_spi_wr (struct ath79_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath79_spi* ath79_spidev_to_sp (struct spi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath79_spi_setup_cs(struct spi_device *spi)
{
	struct ath79_spi *sp = ath79_spidev_to_sp(spi);
	int status;

	status = 0;
	if (gpio_is_valid(spi->cs_gpio)) {
		unsigned long flags;

		flags = GPIOF_DIR_OUT;
		if (spi->mode & SPI_CS_HIGH)
			flags |= GPIOF_INIT_LOW;
		else
			flags |= GPIOF_INIT_HIGH;

		status = gpio_request_one(spi->cs_gpio, flags,
					  dev_name(&spi->dev));
	} else {
		u32 cs_bit = AR71XX_SPI_IOC_CS(spi->chip_select);

		if (spi->mode & SPI_CS_HIGH)
			sp->ioc_base &= ~cs_bit;
		else
			sp->ioc_base |= cs_bit;

		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, sp->ioc_base);
	}

	return status;
}