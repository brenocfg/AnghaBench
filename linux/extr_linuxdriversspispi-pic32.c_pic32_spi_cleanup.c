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
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pic32_spi_cleanup(struct spi_device *spi)
{
	/* de-activate cs-gpio */
	gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));
}