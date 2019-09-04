#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int mode; TYPE_1__* controller; int /*<<< orphan*/  cs_gpio; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* set_cs ) (struct spi_device*,int) ;} ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 int SPI_MASTER_GPIO_SS ; 
 int SPI_NO_CS ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct spi_device*,int) ; 

__attribute__((used)) static void spi_set_cs(struct spi_device *spi, bool enable)
{
	if (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	if (gpio_is_valid(spi->cs_gpio)) {
		/* Honour the SPI_NO_CS flag */
		if (!(spi->mode & SPI_NO_CS))
			gpio_set_value(spi->cs_gpio, !enable);
		/* Some SPI masters need both GPIO CS & slave_select */
		if ((spi->controller->flags & SPI_MASTER_GPIO_SS) &&
		    spi->controller->set_cs)
			spi->controller->set_cs(spi, !enable);
	} else if (spi->controller->set_cs) {
		spi->controller->set_cs(spi, !enable);
	}
}