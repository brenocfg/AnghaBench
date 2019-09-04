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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct l4f00242t03_priv {int /*<<< orphan*/  core_reg; int /*<<< orphan*/  io_reg; } ;
struct l4f00242t03_pdata {int /*<<< orphan*/  data_enable_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct l4f00242t03_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct l4f00242t03_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void l4f00242t03_lcd_powerdown(struct spi_device *spi)
{
	struct l4f00242t03_pdata *pdata = dev_get_platdata(&spi->dev);
	struct l4f00242t03_priv *priv = spi_get_drvdata(spi);

	dev_dbg(&spi->dev, "Powering down LCD\n");

	gpio_set_value(pdata->data_enable_gpio, 0);

	regulator_disable(priv->io_reg);
	regulator_disable(priv->core_reg);
}