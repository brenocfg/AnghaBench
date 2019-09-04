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
struct wilc {scalar_t__ gpio_irq; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 struct wilc* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  wilc_netdev_cleanup (struct wilc*) ; 

__attribute__((used)) static int wilc_bus_remove(struct spi_device *spi)
{
	struct wilc *wilc = spi_get_drvdata(spi);

	/* free the GPIO in module remove */
	if (wilc->gpio_irq)
		gpiod_put(wilc->gpio_irq);
	wilc_netdev_cleanup(wilc);
	return 0;
}