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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int mcast_flags; int /*<<< orphan*/  mcast_handler_lock; int /*<<< orphan*/  capa_initialized; int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ORIG_CAPA_HAS_MCAST ; 
 int BATADV_TVLV_HANDLER_OGM_CIFNOTFND ; 
 int batadv_mcast_tvlv_flags_get (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_want_ipv4_update (struct batadv_priv*,struct batadv_orig_node*,int) ; 
 int /*<<< orphan*/  batadv_mcast_want_ipv6_update (struct batadv_priv*,struct batadv_orig_node*,int) ; 
 int /*<<< orphan*/  batadv_mcast_want_rtr4_update (struct batadv_priv*,struct batadv_orig_node*,int) ; 
 int /*<<< orphan*/  batadv_mcast_want_rtr6_update (struct batadv_priv*,struct batadv_orig_node*,int) ; 
 int /*<<< orphan*/  batadv_mcast_want_unsnoop_update (struct batadv_priv*,struct batadv_orig_node*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_mcast_tvlv_ogm_handler(struct batadv_priv *bat_priv,
					  struct batadv_orig_node *orig,
					  u8 flags,
					  void *tvlv_value,
					  u16 tvlv_value_len)
{
	bool orig_mcast_enabled = !(flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
	u8 mcast_flags;

	mcast_flags = batadv_mcast_tvlv_flags_get(orig_mcast_enabled,
						  tvlv_value, tvlv_value_len);

	spin_lock_bh(&orig->mcast_handler_lock);

	if (orig_mcast_enabled &&
	    !test_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities)) {
		set_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities);
	} else if (!orig_mcast_enabled &&
		   test_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities)) {
		clear_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities);
	}

	set_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capa_initialized);

	batadv_mcast_want_unsnoop_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_ipv4_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_ipv6_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_rtr4_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_rtr6_update(bat_priv, orig, mcast_flags);

	orig->mcast_flags = mcast_flags;
	spin_unlock_bh(&orig->mcast_handler_lock);
}