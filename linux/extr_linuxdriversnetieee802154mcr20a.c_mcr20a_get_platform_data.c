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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct mcr20a_platform_data {int /*<<< orphan*/  rst_gpio; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcr20a_get_platform_data(struct spi_device *spi,
				    struct mcr20a_platform_data *pdata)
{
	int ret = 0;

	if (!spi->dev.of_node)
		return -EINVAL;

	pdata->rst_gpio = of_get_named_gpio(spi->dev.of_node, "rst_b-gpio", 0);
	dev_dbg(&spi->dev, "rst_b-gpio: %d\n", pdata->rst_gpio);

	return ret;
}