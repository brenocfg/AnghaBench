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
struct spi_master {int dummy; } ;
struct spi_imx_data {int /*<<< orphan*/  clk_per; int /*<<< orphan*/  clk_ipg; scalar_t__ base; int /*<<< orphan*/  bitbang; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MXC_CSPICTRL ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_imx_sdma_exit (struct spi_imx_data*) ; 
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int spi_imx_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);
	int ret;

	spi_bitbang_stop(&spi_imx->bitbang);

	ret = clk_enable(spi_imx->clk_per);
	if (ret)
		return ret;

	ret = clk_enable(spi_imx->clk_ipg);
	if (ret) {
		clk_disable(spi_imx->clk_per);
		return ret;
	}

	writel(0, spi_imx->base + MXC_CSPICTRL);
	clk_disable_unprepare(spi_imx->clk_ipg);
	clk_disable_unprepare(spi_imx->clk_per);
	spi_imx_sdma_exit(spi_imx);
	spi_master_put(master);

	return 0;
}