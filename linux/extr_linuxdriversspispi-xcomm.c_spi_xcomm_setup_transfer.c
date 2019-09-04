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
struct spi_xcomm {scalar_t__ current_speed; } ;
struct spi_transfer {int len; scalar_t__ speed_hz; } ;
struct spi_device {int mode; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 int SPI_3WIRE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  SPI_XCOMM_CLOCK ; 
 unsigned int SPI_XCOMM_SETTINGS_3WIRE ; 
 unsigned int SPI_XCOMM_SETTINGS_CLOCK_DIV_16 ; 
 unsigned int SPI_XCOMM_SETTINGS_CLOCK_DIV_4 ; 
 unsigned int SPI_XCOMM_SETTINGS_CLOCK_DIV_64 ; 
 unsigned int SPI_XCOMM_SETTINGS_CPHA ; 
 unsigned int SPI_XCOMM_SETTINGS_CPOL ; 

__attribute__((used)) static int spi_xcomm_setup_transfer(struct spi_xcomm *spi_xcomm,
	struct spi_device *spi, struct spi_transfer *t, unsigned int *settings)
{
	if (t->len > 62)
		return -EINVAL;

	if (t->speed_hz != spi_xcomm->current_speed) {
		unsigned int divider;

		divider = DIV_ROUND_UP(SPI_XCOMM_CLOCK, t->speed_hz);
		if (divider >= 64)
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_64;
		else if (divider >= 16)
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_16;
		else
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_4;

		spi_xcomm->current_speed = t->speed_hz;
	}

	if (spi->mode & SPI_CPOL)
		*settings |= SPI_XCOMM_SETTINGS_CPOL;
	else
		*settings &= ~SPI_XCOMM_SETTINGS_CPOL;

	if (spi->mode & SPI_CPHA)
		*settings &= ~SPI_XCOMM_SETTINGS_CPHA;
	else
		*settings |= SPI_XCOMM_SETTINGS_CPHA;

	if (spi->mode & SPI_3WIRE)
		*settings |= SPI_XCOMM_SETTINGS_3WIRE;
	else
		*settings &= ~SPI_XCOMM_SETTINGS_3WIRE;

	return 0;
}