#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ca8210_platform_data* platform_data; struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct ca8210_priv {int /*<<< orphan*/  clk; } ;
struct ca8210_platform_data {int /*<<< orphan*/  extclockfreq; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register_fixed_rate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 struct ca8210_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ca8210_register_ext_clock(struct spi_device *spi)
{
	struct device_node *np = spi->dev.of_node;
	struct ca8210_priv *priv = spi_get_drvdata(spi);
	struct ca8210_platform_data *pdata = spi->dev.platform_data;
	int ret = 0;

	if (!np)
		return -EFAULT;

	priv->clk = clk_register_fixed_rate(
		&spi->dev,
		np->name,
		NULL,
		0,
		pdata->extclockfreq
	);

	if (IS_ERR(priv->clk)) {
		dev_crit(&spi->dev, "Failed to register external clk\n");
		return PTR_ERR(priv->clk);
	}
	ret = of_clk_add_provider(np, of_clk_src_simple_get, priv->clk);
	if (ret) {
		clk_unregister(priv->clk);
		dev_crit(
			&spi->dev,
			"Failed to register external clock as clock provider\n"
		);
	} else {
		dev_info(&spi->dev, "External clock set as clock provider\n");
	}

	return ret;
}