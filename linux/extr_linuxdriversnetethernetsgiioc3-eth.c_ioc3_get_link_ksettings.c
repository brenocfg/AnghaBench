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
struct net_device {int dummy; } ;
struct ioc3_private {int /*<<< orphan*/  ioc3_lock; int /*<<< orphan*/  mii; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioc3_get_link_ksettings(struct net_device *dev,
				   struct ethtool_link_ksettings *cmd)
{
	struct ioc3_private *ip = netdev_priv(dev);

	spin_lock_irq(&ip->ioc3_lock);
	mii_ethtool_get_link_ksettings(&ip->mii, cmd);
	spin_unlock_irq(&ip->ioc3_lock);

	return 0;
}