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
struct smc_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;
struct net_device {unsigned int base_addr; } ;
struct mii_ioctl_data {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,int /*<<< orphan*/ *) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int inw (scalar_t__) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smc_ioctl (struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct smc_private *smc = netdev_priv(dev);
	struct mii_ioctl_data *mii = if_mii(rq);
	int rc = 0;
	u16 saved_bank;
	unsigned int ioaddr = dev->base_addr;
	unsigned long flags;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irqsave(&smc->lock, flags);
	saved_bank = inw(ioaddr + BANK_SELECT);
	SMC_SELECT_BANK(3);
	rc = generic_mii_ioctl(&smc->mii_if, mii, cmd, NULL);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	return rc;
}