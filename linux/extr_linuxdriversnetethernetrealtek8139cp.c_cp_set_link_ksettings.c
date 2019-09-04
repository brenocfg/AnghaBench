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
struct ethtool_link_ksettings {int dummy; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;

/* Variables and functions */
 int mii_ethtool_set_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings const*) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cp_set_link_ksettings(struct net_device *dev,
				 const struct ethtool_link_ksettings *cmd)
{
	struct cp_private *cp = netdev_priv(dev);
	int rc;
	unsigned long flags;

	spin_lock_irqsave(&cp->lock, flags);
	rc = mii_ethtool_set_link_ksettings(&cp->mii_if, cmd);
	spin_unlock_irqrestore(&cp->lock, flags);

	return rc;
}