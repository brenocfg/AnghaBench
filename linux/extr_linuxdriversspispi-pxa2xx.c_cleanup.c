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
struct spi_device {int /*<<< orphan*/  controller; } ;
struct driver_data {scalar_t__ ssp_type; int /*<<< orphan*/  cs_gpiods; } ;
struct chip_data {scalar_t__ gpiod_cs; } ;

/* Variables and functions */
 scalar_t__ CE4100_SSP ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 

__attribute__((used)) static void cleanup(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata(spi);
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);

	if (!chip)
		return;

	if (drv_data->ssp_type != CE4100_SSP && !drv_data->cs_gpiods &&
	    chip->gpiod_cs)
		gpiod_put(chip->gpiod_cs);

	kfree(chip);
}