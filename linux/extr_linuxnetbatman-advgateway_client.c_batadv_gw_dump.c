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
struct sk_buff {int len; } ;
struct netlink_callback {int /*<<< orphan*/  nlh; TYPE_1__* skb; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct batadv_priv {TYPE_3__* algo_ops; } ;
struct batadv_hard_iface {scalar_t__ if_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* dump ) (struct sk_buff*,struct netlink_callback*,struct batadv_priv*) ;} ;
struct TYPE_6__ {TYPE_2__ gw; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_MESH_IFINDEX ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int batadv_netlink_get_ifindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_softif_is_valid (struct net_device*) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct netlink_callback*,struct batadv_priv*) ; 

int batadv_gw_dump(struct sk_buff *msg, struct netlink_callback *cb)
{
	struct batadv_hard_iface *primary_if = NULL;
	struct net *net = sock_net(cb->skb->sk);
	struct net_device *soft_iface;
	struct batadv_priv *bat_priv;
	int ifindex;
	int ret;

	ifindex = batadv_netlink_get_ifindex(cb->nlh,
					     BATADV_ATTR_MESH_IFINDEX);
	if (!ifindex)
		return -EINVAL;

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface || !batadv_softif_is_valid(soft_iface)) {
		ret = -ENODEV;
		goto out;
	}

	bat_priv = netdev_priv(soft_iface);

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if || primary_if->if_status != BATADV_IF_ACTIVE) {
		ret = -ENOENT;
		goto out;
	}

	if (!bat_priv->algo_ops->gw.dump) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	bat_priv->algo_ops->gw.dump(msg, cb, bat_priv);

	ret = msg->len;

out:
	if (primary_if)
		batadv_hardif_put(primary_if);
	if (soft_iface)
		dev_put(soft_iface);

	return ret;
}