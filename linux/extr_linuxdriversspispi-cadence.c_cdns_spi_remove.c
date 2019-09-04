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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cdns_spi {int /*<<< orphan*/  pclk; int /*<<< orphan*/  ref_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_SPI_ER ; 
 int /*<<< orphan*/  CDNS_SPI_ER_DISABLE ; 
 int /*<<< orphan*/  cdns_spi_write (struct cdns_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 struct cdns_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 

__attribute__((used)) static int cdns_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_write(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);

	clk_disable_unprepare(xspi->ref_clk);
	clk_disable_unprepare(xspi->pclk);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	spi_unregister_master(master);

	return 0;
}