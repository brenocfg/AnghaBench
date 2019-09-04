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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  bd; int /*<<< orphan*/  gpd_addr; int /*<<< orphan*/  gpd; } ;
struct msdc_host {int /*<<< orphan*/  mmc; TYPE_1__ dma; int /*<<< orphan*/  card_delaywork; } ;
struct mmc_host {int dummy; } ;
struct gpd {int dummy; } ;
struct bd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ERR_MSG (char*) ; 
 int MAX_BD_NUM ; 
 int MAX_GPD_NUM ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_deinit_hw (struct msdc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msdc_drv_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct msdc_host *host;

	mmc  = platform_get_drvdata(pdev);
	BUG_ON(!mmc);

	host = mmc_priv(mmc);
	BUG_ON(!host);

	ERR_MSG("removed !!!");

	platform_set_drvdata(pdev, NULL);
	mmc_remove_host(host->mmc);
	msdc_deinit_hw(host);

	cancel_delayed_work_sync(&host->card_delaywork);

	dma_free_coherent(&pdev->dev, MAX_GPD_NUM * sizeof(struct gpd),
			  host->dma.gpd, host->dma.gpd_addr);
	dma_free_coherent(&pdev->dev, MAX_BD_NUM  * sizeof(struct bd),
			  host->dma.bd,  host->dma.bd_addr);

	mmc_free_host(host->mmc);

	return 0;
}