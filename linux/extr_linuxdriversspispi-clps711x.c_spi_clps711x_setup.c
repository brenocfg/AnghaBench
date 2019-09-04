#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; struct spi_device* controller_state; TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spi_clps711x_setup(struct spi_device *spi)
{
	if (!spi->controller_state) {
		int ret;

		ret = devm_gpio_request(&spi->master->dev, spi->cs_gpio,
					dev_name(&spi->master->dev));
		if (ret)
			return ret;

		spi->controller_state = spi;
	}

	/* We are expect that SPI-device is not selected */
	gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));

	return 0;
}