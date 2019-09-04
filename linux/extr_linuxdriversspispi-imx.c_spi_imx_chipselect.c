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
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; } ;

/* Variables and functions */
 int BITBANG_CS_INACTIVE ; 
 int SPI_CS_HIGH ; 
 int SPI_NO_CS ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spi_imx_chipselect(struct spi_device *spi, int is_active)
{
	int active = is_active != BITBANG_CS_INACTIVE;
	int dev_is_lowactive = !(spi->mode & SPI_CS_HIGH);

	if (spi->mode & SPI_NO_CS)
		return;

	if (!gpio_is_valid(spi->cs_gpio))
		return;

	gpio_set_value(spi->cs_gpio, dev_is_lowactive ^ active);
}