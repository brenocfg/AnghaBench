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
struct spi_qup {int /*<<< orphan*/  iclk; int /*<<< orphan*/  cclk; } ;
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUP_STATE_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct spi_qup* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_qup_release_dma (struct spi_master*) ; 
 int spi_qup_set_state (struct spi_qup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_qup_remove(struct platform_device *pdev)
{
	struct spi_master *master = dev_get_drvdata(&pdev->dev);
	struct spi_qup *controller = spi_master_get_devdata(master);
	int ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		return ret;

	ret = spi_qup_set_state(controller, QUP_STATE_RESET);
	if (ret)
		return ret;

	spi_qup_release_dma(master);

	clk_disable_unprepare(controller->cclk);
	clk_disable_unprepare(controller->iclk);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}