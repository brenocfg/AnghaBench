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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  vn; } ;
struct batadv_priv {TYPE_2__ tt; TYPE_1__* algo_ops; } ;
struct batadv_hard_iface {scalar_t__ if_status; struct net_device* net_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_ALGO_NAME ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFNAME ; 
 int /*<<< orphan*/  BATADV_ATTR_MESH_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_MESH_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_MESH_IFNAME ; 
 int /*<<< orphan*/  BATADV_ATTR_TT_TTVN ; 
 int /*<<< orphan*/  BATADV_ATTR_VERSION ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 int /*<<< orphan*/  BATADV_SOURCE_VERSION ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 scalar_t__ batadv_mcast_mesh_info_put (struct sk_buff*,struct batadv_priv*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_mesh_info_put(struct sk_buff *msg, struct net_device *soft_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(soft_iface);
	struct batadv_hard_iface *primary_if = NULL;
	struct net_device *hard_iface;
	int ret = -ENOBUFS;

	if (nla_put_string(msg, BATADV_ATTR_VERSION, BATADV_SOURCE_VERSION) ||
	    nla_put_string(msg, BATADV_ATTR_ALGO_NAME,
			   bat_priv->algo_ops->name) ||
	    nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX, soft_iface->ifindex) ||
	    nla_put_string(msg, BATADV_ATTR_MESH_IFNAME, soft_iface->name) ||
	    nla_put(msg, BATADV_ATTR_MESH_ADDRESS, ETH_ALEN,
		    soft_iface->dev_addr) ||
	    nla_put_u8(msg, BATADV_ATTR_TT_TTVN,
		       (u8)atomic_read(&bat_priv->tt.vn)))
		goto out;

#ifdef CONFIG_BATMAN_ADV_BLA
	if (nla_put_u16(msg, BATADV_ATTR_BLA_CRC,
			ntohs(bat_priv->bla.claim_dest.group)))
		goto out;
#endif

	if (batadv_mcast_mesh_info_put(msg, bat_priv))
		goto out;

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (primary_if && primary_if->if_status == BATADV_IF_ACTIVE) {
		hard_iface = primary_if->net_dev;

		if (nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
				hard_iface->ifindex) ||
		    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
				   hard_iface->name) ||
		    nla_put(msg, BATADV_ATTR_HARD_ADDRESS, ETH_ALEN,
			    hard_iface->dev_addr))
			goto out;
	}

	ret = 0;

 out:
	if (primary_if)
		batadv_hardif_put(primary_if);

	return ret;
}