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
struct net_local {int /*<<< orphan*/ * phy_dev; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xemaclite_disable_interrupts (struct net_local*) ; 

__attribute__((used)) static int xemaclite_close(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);

	netif_stop_queue(dev);
	xemaclite_disable_interrupts(lp);
	free_irq(dev->irq, dev);

	if (lp->phy_dev)
		phy_disconnect(lp->phy_dev);
	lp->phy_dev = NULL;

	return 0;
}