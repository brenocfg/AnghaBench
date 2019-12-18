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
struct sk_buff {int dummy; } ;
struct genl_ops {int internal_flags; } ;
struct genl_info {struct batadv_softif_vlan** user_ptr; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  soft_iface; } ;
struct batadv_priv {int /*<<< orphan*/  soft_iface; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int BATADV_FLAG_NEED_HARDIF ; 
 int BATADV_FLAG_NEED_MESH ; 
 int BATADV_FLAG_NEED_VLAN ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_post_doit(const struct genl_ops *ops, struct sk_buff *skb,
			     struct genl_info *info)
{
	struct batadv_hard_iface *hard_iface;
	struct batadv_softif_vlan *vlan;
	struct batadv_priv *bat_priv;

	if (ops->internal_flags & BATADV_FLAG_NEED_HARDIF &&
	    info->user_ptr[1]) {
		hard_iface = info->user_ptr[1];

		batadv_hardif_put(hard_iface);
	}

	if (ops->internal_flags & BATADV_FLAG_NEED_VLAN && info->user_ptr[1]) {
		vlan = info->user_ptr[1];
		batadv_softif_vlan_put(vlan);
	}

	if (ops->internal_flags & BATADV_FLAG_NEED_MESH && info->user_ptr[0]) {
		bat_priv = info->user_ptr[0];
		dev_put(bat_priv->soft_iface);
	}
}