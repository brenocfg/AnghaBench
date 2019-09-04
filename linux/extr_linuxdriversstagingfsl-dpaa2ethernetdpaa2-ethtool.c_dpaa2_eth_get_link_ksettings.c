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
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct dpni_link_state {int options; int /*<<< orphan*/  rate; int /*<<< orphan*/  member_0; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int DPNI_LINK_OPT_AUTONEG ; 
 int DPNI_LINK_OPT_HALF_DUPLEX ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int dpni_get_link_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_link_state*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
dpaa2_eth_get_link_ksettings(struct net_device *net_dev,
			     struct ethtool_link_ksettings *link_settings)
{
	struct dpni_link_state state = {0};
	int err = 0;
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);

	err = dpni_get_link_state(priv->mc_io, 0, priv->mc_token, &state);
	if (err) {
		netdev_err(net_dev, "ERROR %d getting link state\n", err);
		goto out;
	}

	/* At the moment, we have no way of interrogating the DPMAC
	 * from the DPNI side - and for that matter there may exist
	 * no DPMAC at all. So for now we just don't report anything
	 * beyond the DPNI attributes.
	 */
	if (state.options & DPNI_LINK_OPT_AUTONEG)
		link_settings->base.autoneg = AUTONEG_ENABLE;
	if (!(state.options & DPNI_LINK_OPT_HALF_DUPLEX))
		link_settings->base.duplex = DUPLEX_FULL;
	link_settings->base.speed = state.rate;

out:
	return err;
}