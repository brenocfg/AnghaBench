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
struct tc35815_local {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  tc35815_chip_reset (struct net_device*) ; 
 int /*<<< orphan*/  tc35815_free_queues (struct net_device*) ; 

__attribute__((used)) static int
tc35815_close(struct net_device *dev)
{
	struct tc35815_local *lp = netdev_priv(dev);

	netif_stop_queue(dev);
	napi_disable(&lp->napi);
	if (dev->phydev)
		phy_stop(dev->phydev);
	cancel_work_sync(&lp->restart_work);

	/* Flush the Tx and disable Rx here. */
	tc35815_chip_reset(dev);
	free_irq(dev->irq, dev);

	tc35815_free_queues(dev);

	return 0;

}