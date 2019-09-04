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
struct sh_eth_private {int irq_enabled; scalar_t__ is_opened; TYPE_1__* pdev; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EESIPR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_eth_dev_exit (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_ring_free (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_close(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);

	netif_stop_queue(ndev);

	/* Serialise with the interrupt handler and NAPI, then disable
	 * interrupts.  We have to clear the irq_enabled flag first to
	 * ensure that interrupts won't be re-enabled.
	 */
	mdp->irq_enabled = false;
	synchronize_irq(ndev->irq);
	napi_disable(&mdp->napi);
	sh_eth_write(ndev, 0x0000, EESIPR);

	sh_eth_dev_exit(ndev);

	/* PHY Disconnect */
	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	}

	free_irq(ndev->irq, ndev);

	/* Free all the skbuffs in the Rx queue and the DMA buffer. */
	sh_eth_ring_free(ndev);

	pm_runtime_put_sync(&mdp->pdev->dev);

	mdp->is_opened = 0;

	return 0;
}