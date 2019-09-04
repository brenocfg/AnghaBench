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
struct sis900_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_info; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct sis900_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sis900_get_link_ksettings(struct net_device *net_dev,
				     struct ethtool_link_ksettings *cmd)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	spin_lock_irq(&sis_priv->lock);
	mii_ethtool_get_link_ksettings(&sis_priv->mii_info, cmd);
	spin_unlock_irq(&sis_priv->lock);
	return 0;
}