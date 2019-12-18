#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sw {TYPE_2__* regs; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct TYPE_9__ {TYPE_5__* netdev; TYPE_3__* phydev; } ;
struct TYPE_8__ {int link; int duplex; int speed; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mac_cfg; int /*<<< orphan*/  intr_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAC0_RX_ERROR ; 
 int MAC0_STATUS_CHANGE ; 
 int MAC1_RX_ERROR ; 
 int MAC1_STATUS_CHANGE ; 
 int MAC2_RX_ERROR ; 
 int MAC2_STATUS_CHANGE ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cns3xxx_adjust_link (TYPE_5__*) ; 
 struct sw* netdev_priv (struct net_device*) ; 
 TYPE_4__** switch_port_tab ; 

irqreturn_t eth_stat_irq(int irq, void *pdev)
{
	struct net_device *dev = pdev;
	struct sw *sw = netdev_priv(dev);
	u32 cfg;
	u32 stat = __raw_readl(&sw->regs->intr_stat);
	__raw_writel(0xffffffff, &sw->regs->intr_stat);

	if (stat & MAC2_RX_ERROR)
		switch_port_tab[3]->netdev->stats.rx_dropped++;
	if (stat & MAC1_RX_ERROR)
		switch_port_tab[1]->netdev->stats.rx_dropped++;
	if (stat & MAC0_RX_ERROR)
		switch_port_tab[0]->netdev->stats.rx_dropped++;

	if (stat & MAC0_STATUS_CHANGE) {
		cfg = __raw_readl(&sw->regs->mac_cfg[0]);
		switch_port_tab[0]->phydev->link = (cfg & 0x1);
		switch_port_tab[0]->phydev->duplex = ((cfg >> 4) & 0x1);
		if (((cfg >> 2) & 0x3) == 2)
			switch_port_tab[0]->phydev->speed = 1000;
		else if (((cfg >> 2) & 0x3) == 1)
			switch_port_tab[0]->phydev->speed = 100;
		else
			switch_port_tab[0]->phydev->speed = 10;
		cns3xxx_adjust_link(switch_port_tab[0]->netdev);
	}

	if (stat & MAC1_STATUS_CHANGE) {
		cfg = __raw_readl(&sw->regs->mac_cfg[1]);
		switch_port_tab[1]->phydev->link = (cfg & 0x1);
		switch_port_tab[1]->phydev->duplex = ((cfg >> 4) & 0x1);
		if (((cfg >> 2) & 0x3) == 2)
			switch_port_tab[1]->phydev->speed = 1000;
		else if (((cfg >> 2) & 0x3) == 1)
			switch_port_tab[1]->phydev->speed = 100;
		else
			switch_port_tab[1]->phydev->speed = 10;
		cns3xxx_adjust_link(switch_port_tab[1]->netdev);
	}

	if (stat & MAC2_STATUS_CHANGE) {
		cfg = __raw_readl(&sw->regs->mac_cfg[3]);
		switch_port_tab[3]->phydev->link = (cfg & 0x1);
		switch_port_tab[3]->phydev->duplex = ((cfg >> 4) & 0x1);
		if (((cfg >> 2) & 0x3) == 2)
			switch_port_tab[3]->phydev->speed = 1000;
		else if (((cfg >> 2) & 0x3) == 1)
			switch_port_tab[3]->phydev->speed = 100;
		else
			switch_port_tab[3]->phydev->speed = 10;
		cns3xxx_adjust_link(switch_port_tab[3]->netdev);
	}

	return (IRQ_HANDLED);
}