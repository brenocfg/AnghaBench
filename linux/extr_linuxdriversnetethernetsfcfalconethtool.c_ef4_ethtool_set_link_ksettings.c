#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct ef4_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; int /*<<< orphan*/  net_dev; } ;
struct TYPE_3__ {int (* set_link_ksettings ) (struct ef4_nic*,struct ethtool_link_ksettings const*) ;} ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct ef4_nic*,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int
ef4_ethtool_set_link_ksettings(struct net_device *net_dev,
			       const struct ethtool_link_ksettings *cmd)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	int rc;

	/* GMAC does not support 1000Mbps HD */
	if ((cmd->base.speed == SPEED_1000) &&
	    (cmd->base.duplex != DUPLEX_FULL)) {
		netif_dbg(efx, drv, efx->net_dev,
			  "rejecting unsupported 1000Mbps HD setting\n");
		return -EINVAL;
	}

	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->set_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);
	return rc;
}