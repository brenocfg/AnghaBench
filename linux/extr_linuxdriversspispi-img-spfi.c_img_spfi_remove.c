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
struct img_spfi {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  spfi_clk; int /*<<< orphan*/  dev; scalar_t__ rx_ch; scalar_t__ tx_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ ) ; 
 struct img_spfi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int img_spfi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct img_spfi *spfi = spi_master_get_devdata(master);

	if (spfi->tx_ch)
		dma_release_channel(spfi->tx_ch);
	if (spfi->rx_ch)
		dma_release_channel(spfi->rx_ch);

	pm_runtime_disable(spfi->dev);
	if (!pm_runtime_status_suspended(spfi->dev)) {
		clk_disable_unprepare(spfi->spfi_clk);
		clk_disable_unprepare(spfi->sys_clk);
	}

	return 0;
}