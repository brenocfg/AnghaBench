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
typedef  int u32 ;
struct sw {TYPE_1__* regs; int /*<<< orphan*/  napi; int /*<<< orphan*/  stat_irq; int /*<<< orphan*/  rx_irq; } ;
struct port {size_t id; int /*<<< orphan*/  phydev; struct sw* sw; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_auto_poll_cfg; int /*<<< orphan*/ * mac_cfg; } ;

/* Variables and functions */
 int FS_SUSPEND ; 
 int PORT_DISABLE ; 
 int TS_SUSPEND ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct net_device* napi_dev ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports_open ; 

__attribute__((used)) static int eth_close(struct net_device *dev)
{
	struct port *port = netdev_priv(dev);
	struct sw *sw = port->sw;
	u32 temp;

	ports_open--;

	temp = __raw_readl(&sw->regs->mac_cfg[port->id]);
	temp |= (PORT_DISABLE);
	__raw_writel(temp, &sw->regs->mac_cfg[port->id]);

	netif_stop_queue(dev);

	phy_stop(port->phydev);

	if (!ports_open) {
		disable_irq(sw->rx_irq);
		free_irq(sw->rx_irq, napi_dev);
		disable_irq(sw->stat_irq);
		free_irq(sw->stat_irq, napi_dev);
		napi_disable(&sw->napi);
		netif_stop_queue(napi_dev);
		temp = __raw_readl(&sw->regs->mac_cfg[2]);
		temp |= (PORT_DISABLE);
		__raw_writel(temp, &sw->regs->mac_cfg[2]);

		__raw_writel(TS_SUSPEND | FS_SUSPEND,
			     &sw->regs->dma_auto_poll_cfg);
	}

	netif_carrier_off(dev);
	return 0;
}