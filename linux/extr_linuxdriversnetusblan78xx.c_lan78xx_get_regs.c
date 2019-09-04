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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct lan78xx_net {int dummy; } ;
struct ethtool_regs {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lan78xx_regs ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lan78xx_get_regs(struct net_device *netdev, struct ethtool_regs *regs,
		 void *buf)
{
	u32 *data = buf;
	int i, j;
	struct lan78xx_net *dev = netdev_priv(netdev);

	/* Read Device/MAC registers */
	for (i = 0; i < ARRAY_SIZE(lan78xx_regs); i++)
		lan78xx_read_reg(dev, lan78xx_regs[i], &data[i]);

	if (!netdev->phydev)
		return;

	/* Read PHY registers */
	for (j = 0; j < 32; i++, j++)
		data[i] = phy_read(netdev->phydev, j);
}