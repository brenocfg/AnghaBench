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
struct TYPE_2__ {struct cc2520_platform_data* platform_data; struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cc2520_private {int amplified; void* fifo_pin; } ;
struct cc2520_platform_data {void* reset; void* vreg; void* cca; void* sfd; void* fifop; void* fifo; } ;

/* Variables and functions */
 int ENOENT ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 struct cc2520_private* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cc2520_get_platform_data(struct spi_device *spi,
				    struct cc2520_platform_data *pdata)
{
	struct device_node *np = spi->dev.of_node;
	struct cc2520_private *priv = spi_get_drvdata(spi);

	if (!np) {
		struct cc2520_platform_data *spi_pdata = spi->dev.platform_data;

		if (!spi_pdata)
			return -ENOENT;
		*pdata = *spi_pdata;
		priv->fifo_pin = pdata->fifo;
		return 0;
	}

	pdata->fifo = of_get_named_gpio(np, "fifo-gpio", 0);
	priv->fifo_pin = pdata->fifo;

	pdata->fifop = of_get_named_gpio(np, "fifop-gpio", 0);

	pdata->sfd = of_get_named_gpio(np, "sfd-gpio", 0);
	pdata->cca = of_get_named_gpio(np, "cca-gpio", 0);
	pdata->vreg = of_get_named_gpio(np, "vreg-gpio", 0);
	pdata->reset = of_get_named_gpio(np, "reset-gpio", 0);

	/* CC2591 front end for CC2520 */
	if (of_property_read_bool(np, "amplified"))
		priv->amplified = true;

	return 0;
}