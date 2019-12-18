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
struct TYPE_3__ {int /*<<< orphan*/  bridged; } ;
struct TYPE_4__ {TYPE_1__ mla_flags; } ;
struct batadv_priv {int /*<<< orphan*/  soft_iface; TYPE_2__ mcast; } ;
struct batadv_mcast_querier_state {scalar_t__ shadowing; scalar_t__ exists; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_MCAST ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,char*) ; 
 int /*<<< orphan*/  batadv_info (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
batadv_mcast_querier_log(struct batadv_priv *bat_priv, char *str_proto,
			 struct batadv_mcast_querier_state *old_state,
			 struct batadv_mcast_querier_state *new_state)
{
	if (!old_state->exists && new_state->exists)
		batadv_info(bat_priv->soft_iface, "%s Querier appeared\n",
			    str_proto);
	else if (old_state->exists && !new_state->exists)
		batadv_info(bat_priv->soft_iface,
			    "%s Querier disappeared - multicast optimizations disabled\n",
			    str_proto);
	else if (!bat_priv->mcast.mla_flags.bridged && !new_state->exists)
		batadv_info(bat_priv->soft_iface,
			    "No %s Querier present - multicast optimizations disabled\n",
			    str_proto);

	if (new_state->exists) {
		if ((!old_state->shadowing && new_state->shadowing) ||
		    (!old_state->exists && new_state->shadowing))
			batadv_dbg(BATADV_DBG_MCAST, bat_priv,
				   "%s Querier is behind our bridged segment: Might shadow listeners\n",
				   str_proto);
		else if (old_state->shadowing && !new_state->shadowing)
			batadv_dbg(BATADV_DBG_MCAST, bat_priv,
				   "%s Querier is not behind our bridged segment\n",
				   str_proto);
	}
}