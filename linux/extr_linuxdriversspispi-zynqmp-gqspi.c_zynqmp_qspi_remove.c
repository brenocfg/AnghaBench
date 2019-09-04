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
struct zynqmp_qspi {int /*<<< orphan*/  pclk; int /*<<< orphan*/  refclk; } ;
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_EN_OFST ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 struct zynqmp_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zynqmp_qspi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct zynqmp_qspi *xqspi = spi_master_get_devdata(master);

	zynqmp_gqspi_write(xqspi, GQSPI_EN_OFST, 0x0);
	clk_disable_unprepare(xqspi->refclk);
	clk_disable_unprepare(xqspi->pclk);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	spi_unregister_master(master);

	return 0;
}