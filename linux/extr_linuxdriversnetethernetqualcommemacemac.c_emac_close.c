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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct emac_adapter {int /*<<< orphan*/  reset_lock; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_mac_down (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_rx_tx_rings_free_all (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_close (struct emac_adapter*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int emac_close(struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	mutex_lock(&adpt->reset_lock);

	emac_sgmii_close(adpt);
	emac_mac_down(adpt);
	emac_mac_rx_tx_rings_free_all(adpt);

	free_irq(adpt->irq.irq, &adpt->irq);

	mutex_unlock(&adpt->reset_lock);

	return 0;
}