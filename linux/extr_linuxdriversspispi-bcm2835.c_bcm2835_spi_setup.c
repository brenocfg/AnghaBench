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
struct spi_device {int mode; int chip_select; int /*<<< orphan*/  dev; int /*<<< orphan*/  cs_gpio; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_NO_CS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_spi_setup(struct spi_device *spi)
{
	/*
	 * sanity checking the native-chipselects
	 */
	if (spi->mode & SPI_NO_CS)
		return 0;
	if (gpio_is_valid(spi->cs_gpio))
		return 0;
	if (spi->chip_select > 1) {
		/* error in the case of native CS requested with CS > 1
		 * officially there is a CS2, but it is not documented
		 * which GPIO is connected with that...
		 */
		dev_err(&spi->dev,
			"setup: only two native chip-selects are supported\n");
		return -EINVAL;
	}

	return 0;
}