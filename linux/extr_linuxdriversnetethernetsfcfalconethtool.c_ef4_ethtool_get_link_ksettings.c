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
struct TYPE_4__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct ef4_link_state {scalar_t__ fd; int /*<<< orphan*/  speed; } ;
struct ef4_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; struct ef4_link_state link_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_link_ksettings ) (struct ef4_nic*,struct ethtool_link_ksettings*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ LOOPBACK_INTERNAL (struct ef4_nic*) ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int
ef4_ethtool_get_link_ksettings(struct net_device *net_dev,
			       struct ethtool_link_ksettings *cmd)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	struct ef4_link_state *link_state = &efx->link_state;

	mutex_lock(&efx->mac_lock);
	efx->phy_op->get_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);

	/* Both MACs support pause frames (bidirectional and respond-only) */
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Asym_Pause);

	if (LOOPBACK_INTERNAL(efx)) {
		cmd->base.speed = link_state->speed;
		cmd->base.duplex = link_state->fd ? DUPLEX_FULL : DUPLEX_HALF;
	}

	return 0;
}