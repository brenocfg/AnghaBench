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
struct smsc911x_data {int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {unsigned int rx_dropped; } ;
struct net_device {int /*<<< orphan*/ * phydev; int /*<<< orphan*/  irq; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_CFG ; 
 unsigned int INT_CFG_IRQ_EN_ ; 
 int /*<<< orphan*/  RX_DROP ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_tx_update_txcounters (struct net_device*) ; 

__attribute__((used)) static int smsc911x_stop(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	unsigned int temp;

	/* Disable all device interrupts */
	temp = smsc911x_reg_read(pdata, INT_CFG);
	temp &= ~INT_CFG_IRQ_EN_;
	smsc911x_reg_write(pdata, INT_CFG, temp);

	/* Stop Tx and Rx polling */
	netif_stop_queue(dev);
	napi_disable(&pdata->napi);

	/* At this point all Rx and Tx activity is stopped */
	dev->stats.rx_dropped += smsc911x_reg_read(pdata, RX_DROP);
	smsc911x_tx_update_txcounters(dev);

	free_irq(dev->irq, dev);

	/* Bring the PHY down */
	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
		dev->phydev = NULL;
	}
	netif_carrier_off(dev);

	SMSC_TRACE(pdata, ifdown, "Interface stopped");
	return 0;
}