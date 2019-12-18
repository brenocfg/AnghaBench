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
struct hlist_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mla_lock; } ;
struct batadv_priv {TYPE_1__ mcast; struct net_device* soft_iface; } ;
struct batadv_mcast_mla_flags {int dummy; } ;

/* Variables and functions */
 struct hlist_head HLIST_HEAD_INIT ; 
 int batadv_mcast_mla_bridge_get (struct net_device*,struct hlist_head*,struct batadv_mcast_mla_flags*) ; 
 struct batadv_mcast_mla_flags batadv_mcast_mla_flags_get (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_flags_update (struct batadv_priv*,struct batadv_mcast_mla_flags*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_list_free (struct hlist_head*) ; 
 int batadv_mcast_mla_softif_get (struct net_device*,struct hlist_head*,struct batadv_mcast_mla_flags*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_tt_add (struct batadv_priv*,struct hlist_head*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_tt_retract (struct batadv_priv*,struct hlist_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __batadv_mcast_mla_update(struct batadv_priv *bat_priv)
{
	struct net_device *soft_iface = bat_priv->soft_iface;
	struct hlist_head mcast_list = HLIST_HEAD_INIT;
	struct batadv_mcast_mla_flags flags;
	int ret;

	flags = batadv_mcast_mla_flags_get(bat_priv);

	ret = batadv_mcast_mla_softif_get(soft_iface, &mcast_list, &flags);
	if (ret < 0)
		goto out;

	ret = batadv_mcast_mla_bridge_get(soft_iface, &mcast_list, &flags);
	if (ret < 0)
		goto out;

	spin_lock(&bat_priv->mcast.mla_lock);
	batadv_mcast_mla_tt_retract(bat_priv, &mcast_list);
	batadv_mcast_mla_tt_add(bat_priv, &mcast_list);
	batadv_mcast_mla_flags_update(bat_priv, &flags);
	spin_unlock(&bat_priv->mcast.mla_lock);

out:
	batadv_mcast_mla_list_free(&mcast_list);
}