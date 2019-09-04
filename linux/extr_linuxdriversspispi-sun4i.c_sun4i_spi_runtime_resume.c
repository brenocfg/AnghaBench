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
struct sun4i_spi {int /*<<< orphan*/  hclk; int /*<<< orphan*/  mclk; } ;
struct spi_master {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SUN4I_CTL_ENABLE ; 
 int SUN4I_CTL_MASTER ; 
 int /*<<< orphan*/  SUN4I_CTL_REG ; 
 int SUN4I_CTL_TP ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct spi_master* dev_get_drvdata (struct device*) ; 
 struct sun4i_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  sun4i_spi_write (struct sun4i_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_spi_runtime_resume(struct device *dev)
{
	struct spi_master *master = dev_get_drvdata(dev);
	struct sun4i_spi *sspi = spi_master_get_devdata(master);
	int ret;

	ret = clk_prepare_enable(sspi->hclk);
	if (ret) {
		dev_err(dev, "Couldn't enable AHB clock\n");
		goto out;
	}

	ret = clk_prepare_enable(sspi->mclk);
	if (ret) {
		dev_err(dev, "Couldn't enable module clock\n");
		goto err;
	}

	sun4i_spi_write(sspi, SUN4I_CTL_REG,
			SUN4I_CTL_ENABLE | SUN4I_CTL_MASTER | SUN4I_CTL_TP);

	return 0;

err:
	clk_disable_unprepare(sspi->hclk);
out:
	return ret;
}