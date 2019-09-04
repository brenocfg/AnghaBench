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
struct TYPE_3__ {scalar_t__ autoneg; scalar_t__ duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct ethsw_port_priv {int /*<<< orphan*/  idx; TYPE_2__* ethsw_data; } ;
struct dpsw_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DPSW_LINK_OPT_AUTONEG ; 
 int /*<<< orphan*/  DPSW_LINK_OPT_HALF_DUPLEX ; 
 scalar_t__ DUPLEX_HALF ; 
 int EACCES ; 
 int dpsw_if_set_link_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_link_cfg*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
ethsw_set_link_ksettings(struct net_device *netdev,
			 const struct ethtool_link_ksettings *link_ksettings)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	struct dpsw_link_cfg cfg = {0};
	int err = 0;

	netdev_dbg(netdev, "Setting link parameters...");

	/* Due to a temporary MC limitation, the DPSW port must be down
	 * in order to be able to change link settings. Taking steps to let
	 * the user know that.
	 */
	if (netif_running(netdev)) {
		netdev_info(netdev, "Sorry, interface must be brought down first.\n");
		return -EACCES;
	}

	cfg.rate = link_ksettings->base.speed;
	if (link_ksettings->base.autoneg == AUTONEG_ENABLE)
		cfg.options |= DPSW_LINK_OPT_AUTONEG;
	else
		cfg.options &= ~DPSW_LINK_OPT_AUTONEG;
	if (link_ksettings->base.duplex  == DUPLEX_HALF)
		cfg.options |= DPSW_LINK_OPT_HALF_DUPLEX;
	else
		cfg.options &= ~DPSW_LINK_OPT_HALF_DUPLEX;

	err = dpsw_if_set_link_cfg(port_priv->ethsw_data->mc_io, 0,
				   port_priv->ethsw_data->dpsw_handle,
				   port_priv->idx,
				   &cfg);
	if (err)
		/* ethtool will be loud enough if we return an error; no point
		 * in putting our own error message on the console by default
		 */
		netdev_dbg(netdev, "ERROR %d setting link cfg", err);

	return err;
}