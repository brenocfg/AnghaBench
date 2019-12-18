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
struct port {size_t id; int /*<<< orphan*/  phydev; scalar_t__ speed; struct sw* sw; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mac_cfg; int /*<<< orphan*/  dma_auto_poll_cfg; int /*<<< orphan*/  intr_mask; } ;

/* Variables and functions */
 int FS_SUSPEND ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int MAC0_RX_ERROR ; 
 int MAC0_STATUS_CHANGE ; 
 int MAC1_RX_ERROR ; 
 int MAC1_STATUS_CHANGE ; 
 int MAC2_RX_ERROR ; 
 int MAC2_STATUS_CHANGE ; 
 int PORT_DISABLE ; 
 int TS_SUSPEND ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_rx_dma (struct sw*) ; 
 int /*<<< orphan*/  eth_rx_irq ; 
 int /*<<< orphan*/  eth_stat_irq ; 
 struct net_device* napi_dev ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports_open ; 
 int /*<<< orphan*/  request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static int eth_open(struct net_device *dev)
{
	struct port *port = netdev_priv(dev);
	struct sw *sw = port->sw;
	u32 temp;

	port->speed = 0;	/* force "link up" message */
	phy_start(port->phydev);

	netif_start_queue(dev);

	if (!ports_open) {
		request_irq(sw->rx_irq, eth_rx_irq, IRQF_SHARED, "gig_switch", napi_dev);
		request_irq(sw->stat_irq, eth_stat_irq, IRQF_SHARED, "gig_stat", napi_dev);
		napi_enable(&sw->napi);
		netif_start_queue(napi_dev);

 		__raw_writel(~(MAC0_STATUS_CHANGE | MAC1_STATUS_CHANGE | MAC2_STATUS_CHANGE |
 			       MAC0_RX_ERROR | MAC1_RX_ERROR | MAC2_RX_ERROR), &sw->regs->intr_mask);

		temp = __raw_readl(&sw->regs->mac_cfg[2]);
		temp &= ~(PORT_DISABLE);
		__raw_writel(temp, &sw->regs->mac_cfg[2]);

		temp = __raw_readl(&sw->regs->dma_auto_poll_cfg);
		temp &= ~(TS_SUSPEND | FS_SUSPEND);
		__raw_writel(temp, &sw->regs->dma_auto_poll_cfg);

		enable_rx_dma(sw);
	}
	temp = __raw_readl(&sw->regs->mac_cfg[port->id]);
	temp &= ~(PORT_DISABLE);
	__raw_writel(temp, &sw->regs->mac_cfg[port->id]);

	ports_open++;
	netif_carrier_on(dev);

	return 0;
}