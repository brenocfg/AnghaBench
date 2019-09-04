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
struct sh_eth_private {int is_opened; TYPE_2__* pdev; int /*<<< orphan*/  napi; TYPE_1__* cd; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int sh_eth_dev_init (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_interrupt ; 
 int sh_eth_phy_start (struct net_device*) ; 
 int sh_eth_ring_init (struct net_device*) ; 

__attribute__((used)) static int sh_eth_open(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int ret;

	pm_runtime_get_sync(&mdp->pdev->dev);

	napi_enable(&mdp->napi);

	ret = request_irq(ndev->irq, sh_eth_interrupt,
			  mdp->cd->irq_flags, ndev->name, ndev);
	if (ret) {
		netdev_err(ndev, "Can not assign IRQ number\n");
		goto out_napi_off;
	}

	/* Descriptor set */
	ret = sh_eth_ring_init(ndev);
	if (ret)
		goto out_free_irq;

	/* device init */
	ret = sh_eth_dev_init(ndev);
	if (ret)
		goto out_free_irq;

	/* PHY control start*/
	ret = sh_eth_phy_start(ndev);
	if (ret)
		goto out_free_irq;

	netif_start_queue(ndev);

	mdp->is_opened = 1;

	return ret;

out_free_irq:
	free_irq(ndev->irq, ndev);
out_napi_off:
	napi_disable(&mdp->napi);
	pm_runtime_put_sync(&mdp->pdev->dev);
	return ret;
}