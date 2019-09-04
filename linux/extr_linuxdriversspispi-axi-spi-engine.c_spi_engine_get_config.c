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
struct spi_device {int mode; } ;

/* Variables and functions */
 int SPI_3WIRE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 unsigned int SPI_ENGINE_CONFIG_3WIRE ; 
 unsigned int SPI_ENGINE_CONFIG_CPHA ; 
 unsigned int SPI_ENGINE_CONFIG_CPOL ; 

__attribute__((used)) static unsigned int spi_engine_get_config(struct spi_device *spi)
{
	unsigned int config = 0;

	if (spi->mode & SPI_CPOL)
		config |= SPI_ENGINE_CONFIG_CPOL;
	if (spi->mode & SPI_CPHA)
		config |= SPI_ENGINE_CONFIG_CPHA;
	if (spi->mode & SPI_3WIRE)
		config |= SPI_ENGINE_CONFIG_3WIRE;

	return config;
}