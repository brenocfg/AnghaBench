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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  mcast_handler_lock; struct batadv_priv* bat_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_MCAST_WANT_NO_RTR4 ; 
 int /*<<< orphan*/  BATADV_MCAST_WANT_NO_RTR6 ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  batadv_mcast_want_ipv4_update (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_want_ipv6_update (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_want_rtr4_update (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_want_rtr6_update (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_want_unsnoop_update (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_mcast_purge_orig(struct batadv_orig_node *orig)
{
	struct batadv_priv *bat_priv = orig->bat_priv;

	spin_lock_bh(&orig->mcast_handler_lock);

	batadv_mcast_want_unsnoop_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_ipv4_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_ipv6_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_rtr4_update(bat_priv, orig,
				      BATADV_MCAST_WANT_NO_RTR4);
	batadv_mcast_want_rtr6_update(bat_priv, orig,
				      BATADV_MCAST_WANT_NO_RTR6);

	spin_unlock_bh(&orig->mcast_handler_lock);
}