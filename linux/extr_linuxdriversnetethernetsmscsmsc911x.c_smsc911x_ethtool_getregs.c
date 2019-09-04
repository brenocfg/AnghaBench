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
typedef  int /*<<< orphan*/  u32 ;
struct smsc911x_data {int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  idrev; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 unsigned int E2P_DATA ; 
 unsigned int ID_REV ; 
 unsigned int MAC_CR ; 
 unsigned int WUCSR ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smsc911x_mac_read (struct smsc911x_data*,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_mii_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_reg_read (struct smsc911x_data*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
smsc911x_ethtool_getregs(struct net_device *dev, struct ethtool_regs *regs,
			 void *buf)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct phy_device *phy_dev = dev->phydev;
	unsigned long flags;
	unsigned int i;
	unsigned int j = 0;
	u32 *data = buf;

	regs->version = pdata->idrev;
	for (i = ID_REV; i <= E2P_DATA; i += (sizeof(u32)))
		data[j++] = smsc911x_reg_read(pdata, i);

	for (i = MAC_CR; i <= WUCSR; i++) {
		spin_lock_irqsave(&pdata->mac_lock, flags);
		data[j++] = smsc911x_mac_read(pdata, i);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);
	}

	for (i = 0; i <= 31; i++)
		data[j++] = smsc911x_mii_read(phy_dev->mdio.bus,
					      phy_dev->mdio.addr, i);
}