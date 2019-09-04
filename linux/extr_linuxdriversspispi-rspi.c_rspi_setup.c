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
struct spi_device {int mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  master; } ;
struct rspi_data {int /*<<< orphan*/  sppcr; int /*<<< orphan*/  spcmd; int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPCMD_CPHA ; 
 int /*<<< orphan*/  SPCMD_CPOL ; 
 int /*<<< orphan*/  SPCMD_SSLKP ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int /*<<< orphan*/  SPPCR_SPLP ; 
 int /*<<< orphan*/  set_config_register (struct rspi_data*,int) ; 
 struct rspi_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_setup(struct spi_device *spi)
{
	struct rspi_data *rspi = spi_master_get_devdata(spi->master);

	rspi->max_speed_hz = spi->max_speed_hz;

	rspi->spcmd = SPCMD_SSLKP;
	if (spi->mode & SPI_CPOL)
		rspi->spcmd |= SPCMD_CPOL;
	if (spi->mode & SPI_CPHA)
		rspi->spcmd |= SPCMD_CPHA;

	/* CMOS output mode and MOSI signal from previous transfer */
	rspi->sppcr = 0;
	if (spi->mode & SPI_LOOP)
		rspi->sppcr |= SPPCR_SPLP;

	set_config_register(rspi, 8);

	return 0;
}