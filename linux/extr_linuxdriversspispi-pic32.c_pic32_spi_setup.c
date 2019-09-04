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
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_spi_setup(struct spi_device *spi)
{
	if (!spi->max_speed_hz) {
		dev_err(&spi->dev, "No max speed HZ parameter\n");
		return -EINVAL;
	}

	/* PIC32 spi controller can drive /CS during transfer depending
	 * on tx fifo fill-level. /CS will stay asserted as long as TX
	 * fifo is non-empty, else will be deasserted indicating
	 * completion of the ongoing transfer. This might result into
	 * unreliable/erroneous SPI transactions.
	 * To avoid that we will always handle /CS by toggling GPIO.
	 */
	if (!gpio_is_valid(spi->cs_gpio))
		return -EINVAL;

	gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));

	return 0;
}