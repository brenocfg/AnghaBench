#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ dual_emac; } ;
struct cpsw_common {TYPE_2__* slaves; TYPE_1__ data; int /*<<< orphan*/  dma; int /*<<< orphan*/  cpts; } ;
struct TYPE_4__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_remove_dt (struct platform_device*) ; 
 int /*<<< orphan*/  cpts_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int cpsw_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	int ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(&pdev->dev);
		return ret;
	}

	if (cpsw->data.dual_emac)
		unregister_netdev(cpsw->slaves[1].ndev);
	unregister_netdev(ndev);

	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
	cpsw_remove_dt(pdev);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	if (cpsw->data.dual_emac)
		free_netdev(cpsw->slaves[1].ndev);
	free_netdev(ndev);
	return 0;
}