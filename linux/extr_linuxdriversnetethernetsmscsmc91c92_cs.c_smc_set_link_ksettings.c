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
typedef  int u16 ;
struct smc_private {int cfg; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;
struct net_device {unsigned int base_addr; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int CFG_MII_SELECT ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int inw (scalar_t__) ; 
 int mii_ethtool_set_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings const*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int smc_netdev_set_ecmd (struct net_device*,struct ethtool_link_ksettings const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smc_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *ecmd)
{
	struct smc_private *smc = netdev_priv(dev);
	unsigned int ioaddr = dev->base_addr;
	u16 saved_bank = inw(ioaddr + BANK_SELECT);
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&smc->lock, flags);
	SMC_SELECT_BANK(3);
	if (smc->cfg & CFG_MII_SELECT)
		ret = mii_ethtool_set_link_ksettings(&smc->mii_if, ecmd);
	else
		ret = smc_netdev_set_ecmd(dev, ecmd);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	return ret;
}