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
struct tegra_slink_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
struct spi_master {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct spi_master* dev_get_drvdata (struct device*) ; 
 struct tegra_slink_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int tegra_slink_runtime_resume(struct device *dev)
{
	struct spi_master *master = dev_get_drvdata(dev);
	struct tegra_slink_data *tspi = spi_master_get_devdata(master);
	int ret;

	ret = clk_prepare_enable(tspi->clk);
	if (ret < 0) {
		dev_err(tspi->dev, "clk_prepare failed: %d\n", ret);
		return ret;
	}
	return 0;
}