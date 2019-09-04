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
struct wilc {struct gpio_desc* gpio_irq; int /*<<< orphan*/ * dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIO_NUM ; 
 int /*<<< orphan*/  HIF_SPI ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* gpio_to_desc (int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wilc*) ; 
 int /*<<< orphan*/  wilc_hif_spi ; 
 int wilc_netdev_init (struct wilc**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wilc_bus_probe(struct spi_device *spi)
{
	int ret;
	struct wilc *wilc;
	struct gpio_desc *gpio;

	gpio = gpiod_get(&spi->dev, "irq", GPIOD_IN);
	if (IS_ERR(gpio)) {
		/* get the GPIO descriptor from hardcode GPIO number */
		gpio = gpio_to_desc(GPIO_NUM);
		if (!gpio)
			dev_err(&spi->dev, "failed to get the irq gpio\n");
	}

	ret = wilc_netdev_init(&wilc, NULL, HIF_SPI, &wilc_hif_spi);
	if (ret)
		return ret;

	spi_set_drvdata(spi, wilc);
	wilc->dev = &spi->dev;
	wilc->gpio_irq = gpio;

	return 0;
}