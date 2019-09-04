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
struct smc_local {scalar_t__ phy_type; int ctl_rfduplx; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; scalar_t__ port; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ PORT_AUI ; 
 scalar_t__ PORT_TP ; 
 scalar_t__ SPEED_10 ; 
 int mii_ethtool_set_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings const*) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smc_ethtool_set_link_ksettings(struct net_device *dev,
			       const struct ethtool_link_ksettings *cmd)
{
	struct smc_local *lp = netdev_priv(dev);
	int ret;

	if (lp->phy_type != 0) {
		spin_lock_irq(&lp->lock);
		ret = mii_ethtool_set_link_ksettings(&lp->mii, cmd);
		spin_unlock_irq(&lp->lock);
	} else {
		if (cmd->base.autoneg != AUTONEG_DISABLE ||
		    cmd->base.speed != SPEED_10 ||
		    (cmd->base.duplex != DUPLEX_HALF &&
		     cmd->base.duplex != DUPLEX_FULL) ||
		    (cmd->base.port != PORT_TP && cmd->base.port != PORT_AUI))
			return -EINVAL;

//		lp->port = cmd->base.port;
		lp->ctl_rfduplx = cmd->base.duplex == DUPLEX_FULL;

//		if (netif_running(dev))
//			smc_set_port(dev);

		ret = 0;
	}

	return ret;
}