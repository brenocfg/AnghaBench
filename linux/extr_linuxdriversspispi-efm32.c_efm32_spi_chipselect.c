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
struct spi_device {int mode; size_t chip_select; int /*<<< orphan*/  master; } ;
struct efm32_spi_ddata {int /*<<< orphan*/ * csgpio; } ;

/* Variables and functions */
 int BITBANG_CS_ACTIVE ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct efm32_spi_ddata* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efm32_spi_chipselect(struct spi_device *spi, int is_on)
{
	struct efm32_spi_ddata *ddata = spi_master_get_devdata(spi->master);
	int value = !(spi->mode & SPI_CS_HIGH) == !(is_on == BITBANG_CS_ACTIVE);

	gpio_set_value(ddata->csgpio[spi->chip_select], value);
}