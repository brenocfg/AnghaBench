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
struct net_device {int dummy; } ;
struct hlist_head {int dummy; } ;
struct batadv_priv {struct net_device* soft_iface; } ;

/* Variables and functions */
 struct hlist_head HLIST_HEAD_INIT ; 
 int batadv_mcast_mla_bridge_get (struct batadv_priv*,struct net_device*,struct hlist_head*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_list_free (struct hlist_head*) ; 
 int batadv_mcast_mla_softif_get (struct batadv_priv*,struct net_device*,struct hlist_head*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_tt_add (struct batadv_priv*,struct hlist_head*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_tt_retract (struct batadv_priv*,struct hlist_head*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_tvlv_update (struct batadv_priv*) ; 

__attribute__((used)) static void __batadv_mcast_mla_update(struct batadv_priv *bat_priv)
{
	struct net_device *soft_iface = bat_priv->soft_iface;
	struct hlist_head mcast_list = HLIST_HEAD_INIT;
	int ret;

	if (!batadv_mcast_mla_tvlv_update(bat_priv))
		goto update;

	ret = batadv_mcast_mla_softif_get(bat_priv, soft_iface, &mcast_list);
	if (ret < 0)
		goto out;

	ret = batadv_mcast_mla_bridge_get(bat_priv, soft_iface, &mcast_list);
	if (ret < 0)
		goto out;

update:
	batadv_mcast_mla_tt_retract(bat_priv, &mcast_list);
	batadv_mcast_mla_tt_add(bat_priv, &mcast_list);

out:
	batadv_mcast_mla_list_free(&mcast_list);
}