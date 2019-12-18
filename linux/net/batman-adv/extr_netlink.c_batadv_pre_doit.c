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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  soft_iface; } ;
struct net {int dummy; } ;
struct genl_ops {int internal_flags; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  soft_iface; } ;
struct batadv_priv {int /*<<< orphan*/  soft_iface; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int BATADV_FLAG_NEED_HARDIF ; 
 int BATADV_FLAG_NEED_MESH ; 
 int BATADV_FLAG_NEED_VLAN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct net_device* batadv_get_hardif_from_info (struct net_device*,struct net*,struct genl_info*) ; 
 struct net_device* batadv_get_softif_from_info (struct net*,struct genl_info*) ; 
 struct net_device* batadv_get_vlan_from_info (struct net_device*,struct net*,struct genl_info*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int hweight8 (int) ; 
 struct net_device* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int batadv_pre_doit(const struct genl_ops *ops, struct sk_buff *skb,
			   struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct batadv_hard_iface *hard_iface;
	struct batadv_priv *bat_priv = NULL;
	struct batadv_softif_vlan *vlan;
	struct net_device *soft_iface;
	u8 user_ptr1_flags;
	u8 mesh_dep_flags;
	int ret;

	user_ptr1_flags = BATADV_FLAG_NEED_HARDIF | BATADV_FLAG_NEED_VLAN;
	if (WARN_ON(hweight8(ops->internal_flags & user_ptr1_flags) > 1))
		return -EINVAL;

	mesh_dep_flags = BATADV_FLAG_NEED_HARDIF | BATADV_FLAG_NEED_VLAN;
	if (WARN_ON((ops->internal_flags & mesh_dep_flags) &&
		    (~ops->internal_flags & BATADV_FLAG_NEED_MESH)))
		return -EINVAL;

	if (ops->internal_flags & BATADV_FLAG_NEED_MESH) {
		soft_iface = batadv_get_softif_from_info(net, info);
		if (IS_ERR(soft_iface))
			return PTR_ERR(soft_iface);

		bat_priv = netdev_priv(soft_iface);
		info->user_ptr[0] = bat_priv;
	}

	if (ops->internal_flags & BATADV_FLAG_NEED_HARDIF) {
		hard_iface = batadv_get_hardif_from_info(bat_priv, net, info);
		if (IS_ERR(hard_iface)) {
			ret = PTR_ERR(hard_iface);
			goto err_put_softif;
		}

		info->user_ptr[1] = hard_iface;
	}

	if (ops->internal_flags & BATADV_FLAG_NEED_VLAN) {
		vlan = batadv_get_vlan_from_info(bat_priv, net, info);
		if (IS_ERR(vlan)) {
			ret = PTR_ERR(vlan);
			goto err_put_softif;
		}

		info->user_ptr[1] = vlan;
	}

	return 0;

err_put_softif:
	if (bat_priv)
		dev_put(bat_priv->soft_iface);

	return ret;
}