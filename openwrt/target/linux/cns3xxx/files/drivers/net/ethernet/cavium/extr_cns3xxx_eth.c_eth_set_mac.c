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
struct sw {TYPE_1__* regs; } ;
struct sockaddr {int* sa_data; } ;
struct port {int id; struct sw* sw; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  arl_vlan_cmd; int /*<<< orphan*/ * arl_ctrl; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int eth_set_mac(struct net_device *netdev, void *p)
{
	struct port *port = netdev_priv(netdev);
	struct sw *sw = port->sw;
	struct sockaddr *addr = p;
	u32 cycles = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* Invalidate old ARL Entry */
	if (port->id == 3)
		__raw_writel((port->id << 16) | (0x4 << 9), &sw->regs->arl_ctrl[0]);
	else
		__raw_writel(((port->id + 1) << 16) | (0x4 << 9), &sw->regs->arl_ctrl[0]);
	__raw_writel( ((netdev->dev_addr[0] << 24) | (netdev->dev_addr[1] << 16) |
			(netdev->dev_addr[2] << 8) | (netdev->dev_addr[3])),
			&sw->regs->arl_ctrl[1]);

	__raw_writel( ((netdev->dev_addr[4] << 24) | (netdev->dev_addr[5] << 16) |
			(1 << 1)),
			&sw->regs->arl_ctrl[2]);
	__raw_writel((1 << 19), &sw->regs->arl_vlan_cmd);

	while (((__raw_readl(&sw->regs->arl_vlan_cmd) & (1 << 21)) == 0)
			&& cycles < 5000) {
		udelay(1);
		cycles++;
	}

	cycles = 0;
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	if (port->id == 3)
		__raw_writel((port->id << 16) | (0x4 << 9), &sw->regs->arl_ctrl[0]);
	else
		__raw_writel(((port->id + 1) << 16) | (0x4 << 9), &sw->regs->arl_ctrl[0]);
	__raw_writel( ((addr->sa_data[0] << 24) | (addr->sa_data[1] << 16) |
			(addr->sa_data[2] << 8) | (addr->sa_data[3])),
			&sw->regs->arl_ctrl[1]);

	__raw_writel( ((addr->sa_data[4] << 24) | (addr->sa_data[5] << 16) |
			(7 << 4) | (1 << 1)), &sw->regs->arl_ctrl[2]);
	__raw_writel((1 << 19), &sw->regs->arl_vlan_cmd);

	while (((__raw_readl(&sw->regs->arl_vlan_cmd) & (1 << 21)) == 0)
		&& cycles < 5000) {
		udelay(1);
		cycles++;
	}
	return 0;
}