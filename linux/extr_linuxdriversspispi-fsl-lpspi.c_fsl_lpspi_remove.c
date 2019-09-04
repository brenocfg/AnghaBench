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
struct platform_device {int dummy; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 struct fsl_lpspi_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int fsl_lpspi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct fsl_lpspi_data *fsl_lpspi = spi_master_get_devdata(master);

	clk_disable_unprepare(fsl_lpspi->clk);

	return 0;
}