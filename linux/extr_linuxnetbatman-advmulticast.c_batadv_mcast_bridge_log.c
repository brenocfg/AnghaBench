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
struct TYPE_2__ {int /*<<< orphan*/  querier_ipv6; int /*<<< orphan*/  querier_ipv4; scalar_t__ bridged; } ;
struct batadv_priv {TYPE_1__ mcast; } ;
struct batadv_mcast_querier_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_MCAST ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*) ; 
 int /*<<< orphan*/  batadv_mcast_querier_log (struct batadv_priv*,char*,int /*<<< orphan*/ *,struct batadv_mcast_querier_state*) ; 

__attribute__((used)) static void
batadv_mcast_bridge_log(struct batadv_priv *bat_priv, bool bridged,
			struct batadv_mcast_querier_state *querier_ipv4,
			struct batadv_mcast_querier_state *querier_ipv6)
{
	if (!bat_priv->mcast.bridged && bridged)
		batadv_dbg(BATADV_DBG_MCAST, bat_priv,
			   "Bridge added: Setting Unsnoopables(U)-flag\n");
	else if (bat_priv->mcast.bridged && !bridged)
		batadv_dbg(BATADV_DBG_MCAST, bat_priv,
			   "Bridge removed: Unsetting Unsnoopables(U)-flag\n");

	if (bridged) {
		batadv_mcast_querier_log(bat_priv, "IGMP",
					 &bat_priv->mcast.querier_ipv4,
					 querier_ipv4);
		batadv_mcast_querier_log(bat_priv, "MLD",
					 &bat_priv->mcast.querier_ipv6,
					 querier_ipv6);
	}
}