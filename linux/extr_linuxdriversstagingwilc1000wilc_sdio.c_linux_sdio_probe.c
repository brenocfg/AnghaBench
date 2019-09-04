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
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_device_id {int dummy; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_WILC1000_HW_OOB_INTR ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIO_NUM ; 
 int /*<<< orphan*/  HIF_SDIO ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* gpio_to_desc (int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct wilc*) ; 
 int /*<<< orphan*/  wilc_hif_sdio ; 
 int wilc_netdev_init (struct wilc**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int linux_sdio_probe(struct sdio_func *func,
			    const struct sdio_device_id *id)
{
	struct wilc *wilc;
	int ret;
	struct gpio_desc *gpio = NULL;

	if (IS_ENABLED(CONFIG_WILC1000_HW_OOB_INTR)) {
		gpio = gpiod_get(&func->dev, "irq", GPIOD_IN);
		if (IS_ERR(gpio)) {
			/* get the GPIO descriptor from hardcode GPIO number */
			gpio = gpio_to_desc(GPIO_NUM);
			if (!gpio)
				dev_err(&func->dev, "failed to get irq gpio\n");
		}
	}

	dev_dbg(&func->dev, "Initializing netdev\n");
	ret = wilc_netdev_init(&wilc, &func->dev, HIF_SDIO, &wilc_hif_sdio);
	if (ret) {
		dev_err(&func->dev, "Couldn't initialize netdev\n");
		return ret;
	}
	sdio_set_drvdata(func, wilc);
	wilc->dev = &func->dev;
	wilc->gpio_irq = gpio;

	dev_info(&func->dev, "Driver Initializing success\n");
	return 0;
}