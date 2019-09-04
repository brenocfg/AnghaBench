#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct batadv_tvlv_mcast_data {int flags; int /*<<< orphan*/  reserved; } ;
struct TYPE_5__ {void* shadowing; void* exists; } ;
struct TYPE_4__ {void* shadowing; void* exists; } ;
struct TYPE_6__ {int bridged; int enabled; int flags; TYPE_2__ querier_ipv6; TYPE_1__ querier_ipv4; } ;
struct batadv_priv {TYPE_3__ mcast; struct net_device* soft_iface; } ;
struct batadv_mcast_querier_state {int member_0; int member_1; void* shadowing; void* exists; } ;
typedef  int /*<<< orphan*/  mcast_data ;

/* Variables and functions */
 int BATADV_MCAST_WANT_ALL_IPV4 ; 
 int BATADV_MCAST_WANT_ALL_IPV6 ; 
 int BATADV_MCAST_WANT_ALL_UNSNOOPABLES ; 
 int BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  BATADV_TVLV_MCAST ; 
 int /*<<< orphan*/  CONFIG_BRIDGE_IGMP_SNOOPING ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_bridge_log (struct batadv_priv*,int,struct batadv_mcast_querier_state*,struct batadv_mcast_querier_state*) ; 
 int /*<<< orphan*/  batadv_mcast_flags_log (struct batadv_priv*,int) ; 
 int batadv_mcast_has_bridge (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tvlv_container_register (struct batadv_priv*,int /*<<< orphan*/ ,int,struct batadv_tvlv_mcast_data*,int) ; 
 void* br_multicast_has_querier_adjacent (struct net_device*,int /*<<< orphan*/ ) ; 
 void* br_multicast_has_querier_anywhere (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 

__attribute__((used)) static bool batadv_mcast_mla_tvlv_update(struct batadv_priv *bat_priv)
{
	struct batadv_tvlv_mcast_data mcast_data;
	struct batadv_mcast_querier_state querier4 = {false, false};
	struct batadv_mcast_querier_state querier6 = {false, false};
	struct net_device *dev = bat_priv->soft_iface;
	bool bridged;

	mcast_data.flags = BATADV_NO_FLAGS;
	memset(mcast_data.reserved, 0, sizeof(mcast_data.reserved));

	bridged = batadv_mcast_has_bridge(bat_priv);
	if (!bridged)
		goto update;

	if (!IS_ENABLED(CONFIG_BRIDGE_IGMP_SNOOPING))
		pr_warn_once("No bridge IGMP snooping compiled - multicast optimizations disabled\n");

	querier4.exists = br_multicast_has_querier_anywhere(dev, ETH_P_IP);
	querier4.shadowing = br_multicast_has_querier_adjacent(dev, ETH_P_IP);

	querier6.exists = br_multicast_has_querier_anywhere(dev, ETH_P_IPV6);
	querier6.shadowing = br_multicast_has_querier_adjacent(dev, ETH_P_IPV6);

	mcast_data.flags |= BATADV_MCAST_WANT_ALL_UNSNOOPABLES;

	/* 1) If no querier exists at all, then multicast listeners on
	 *    our local TT clients behind the bridge will keep silent.
	 * 2) If the selected querier is on one of our local TT clients,
	 *    behind the bridge, then this querier might shadow multicast
	 *    listeners on our local TT clients, behind this bridge.
	 *
	 * In both cases, we will signalize other batman nodes that
	 * we need all multicast traffic of the according protocol.
	 */
	if (!querier4.exists || querier4.shadowing)
		mcast_data.flags |= BATADV_MCAST_WANT_ALL_IPV4;

	if (!querier6.exists || querier6.shadowing)
		mcast_data.flags |= BATADV_MCAST_WANT_ALL_IPV6;

update:
	batadv_mcast_bridge_log(bat_priv, bridged, &querier4, &querier6);

	bat_priv->mcast.querier_ipv4.exists = querier4.exists;
	bat_priv->mcast.querier_ipv4.shadowing = querier4.shadowing;

	bat_priv->mcast.querier_ipv6.exists = querier6.exists;
	bat_priv->mcast.querier_ipv6.shadowing = querier6.shadowing;

	bat_priv->mcast.bridged = bridged;

	if (!bat_priv->mcast.enabled ||
	    mcast_data.flags != bat_priv->mcast.flags) {
		batadv_mcast_flags_log(bat_priv, mcast_data.flags);
		batadv_tvlv_container_register(bat_priv, BATADV_TVLV_MCAST, 2,
					       &mcast_data, sizeof(mcast_data));
		bat_priv->mcast.flags = mcast_data.flags;
		bat_priv->mcast.enabled = true;
	}

	return !(mcast_data.flags & BATADV_MCAST_WANT_ALL_IPV4 &&
		 mcast_data.flags & BATADV_MCAST_WANT_ALL_IPV6);
}