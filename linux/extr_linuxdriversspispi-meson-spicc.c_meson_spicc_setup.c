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
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; scalar_t__ controller_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_spicc_setup(struct spi_device *spi)
{
	int ret = 0;

	if (!spi->controller_state)
		spi->controller_state = spi_master_get_devdata(spi->master);
	else if (gpio_is_valid(spi->cs_gpio))
		goto out_gpio;
	else if (spi->cs_gpio == -ENOENT)
		return 0;

	if (gpio_is_valid(spi->cs_gpio)) {
		ret = gpio_request(spi->cs_gpio, dev_name(&spi->dev));
		if (ret) {
			dev_err(&spi->dev, "failed to request cs gpio\n");
			return ret;
		}
	}

out_gpio:
	ret = gpio_direction_output(spi->cs_gpio,
			!(spi->mode & SPI_CS_HIGH));

	return ret;
}