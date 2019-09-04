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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ autoneg; scalar_t__ duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct dpni_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; int /*<<< orphan*/  member_0; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DPNI_DYNAMIC_LINK_SET_VER_MAJOR ; 
 int /*<<< orphan*/  DPNI_DYNAMIC_LINK_SET_VER_MINOR ; 
 int /*<<< orphan*/  DPNI_LINK_OPT_AUTONEG ; 
 int /*<<< orphan*/  DPNI_LINK_OPT_HALF_DUPLEX ; 
 scalar_t__ DUPLEX_HALF ; 
 int EACCES ; 
 scalar_t__ dpaa2_eth_cmp_dpni_ver (struct dpaa2_eth_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpni_set_link_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_link_cfg*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
dpaa2_eth_set_link_ksettings(struct net_device *net_dev,
			     const struct ethtool_link_ksettings *link_settings)
{
	struct dpni_link_cfg cfg = {0};
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	int err = 0;

	/* If using an older MC version, the DPNI must be down
	 * in order to be able to change link settings. Taking steps to let
	 * the user know that.
	 */
	if (dpaa2_eth_cmp_dpni_ver(priv, DPNI_DYNAMIC_LINK_SET_VER_MAJOR,
				   DPNI_DYNAMIC_LINK_SET_VER_MINOR) < 0) {
		if (netif_running(net_dev)) {
			netdev_info(net_dev, "Interface must be brought down first.\n");
			return -EACCES;
		}
	}

	cfg.rate = link_settings->base.speed;
	if (link_settings->base.autoneg == AUTONEG_ENABLE)
		cfg.options |= DPNI_LINK_OPT_AUTONEG;
	else
		cfg.options &= ~DPNI_LINK_OPT_AUTONEG;
	if (link_settings->base.duplex  == DUPLEX_HALF)
		cfg.options |= DPNI_LINK_OPT_HALF_DUPLEX;
	else
		cfg.options &= ~DPNI_LINK_OPT_HALF_DUPLEX;

	err = dpni_set_link_cfg(priv->mc_io, 0, priv->mc_token, &cfg);
	if (err)
		/* ethtool will be loud enough if we return an error; no point
		 * in putting our own error message on the console by default
		 */
		netdev_dbg(net_dev, "ERROR %d setting link cfg\n", err);

	return err;
}