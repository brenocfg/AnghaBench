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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 size_t BATADV_ATTR_MESH_IFINDEX ; 
 size_t BATADV_ATTR_ORIG_ADDRESS ; 
 int /*<<< orphan*/  BATADV_TP_REASON_CANCEL ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  batadv_softif_is_valid (struct net_device*) ; 
 int /*<<< orphan*/  batadv_tp_stop (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 int nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_tp_meter_cancel(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct net_device *soft_iface;
	struct batadv_priv *bat_priv;
	int ifindex;
	u8 *dst;
	int ret = 0;

	if (!info->attrs[BATADV_ATTR_MESH_IFINDEX])
		return -EINVAL;

	if (!info->attrs[BATADV_ATTR_ORIG_ADDRESS])
		return -EINVAL;

	ifindex = nla_get_u32(info->attrs[BATADV_ATTR_MESH_IFINDEX]);
	if (!ifindex)
		return -EINVAL;

	dst = nla_data(info->attrs[BATADV_ATTR_ORIG_ADDRESS]);

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface || !batadv_softif_is_valid(soft_iface)) {
		ret = -ENODEV;
		goto out;
	}

	bat_priv = netdev_priv(soft_iface);
	batadv_tp_stop(bat_priv, dst, BATADV_TP_REASON_CANCEL);

out:
	if (soft_iface)
		dev_put(soft_iface);

	return ret;
}