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
struct butterfly {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int BITBANG_CS_INACTIVE ; 
 scalar_t__ PARPORT_CONTROL_INIT ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  parport_frob_control (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setsck (struct spi_device*,int) ; 
 scalar_t__ spi_cs_bit ; 
 struct butterfly* spidev_to_pp (struct spi_device*) ; 

__attribute__((used)) static void butterfly_chipselect(struct spi_device *spi, int value)
{
	struct butterfly	*pp = spidev_to_pp(spi);

	/* set default clock polarity */
	if (value != BITBANG_CS_INACTIVE)
		setsck(spi, spi->mode & SPI_CPOL);

	/* here, value == "activate or not";
	 * most PARPORT_CONTROL_* bits are negated, so we must
	 * morph it to value == "bit value to write in control register"
	 */
	if (spi_cs_bit == PARPORT_CONTROL_INIT)
		value = !value;

	parport_frob_control(pp->port, spi_cs_bit, value ? spi_cs_bit : 0);
}