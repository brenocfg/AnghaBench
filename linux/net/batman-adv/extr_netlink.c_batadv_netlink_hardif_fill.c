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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct netlink_callback {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct batadv_priv {TYPE_1__* soft_iface; } ;
struct TYPE_4__ {int /*<<< orphan*/  throughput_override; int /*<<< orphan*/  elp_interval; } ;
struct batadv_hard_iface {scalar_t__ if_status; TYPE_2__ bat_v; struct net_device* net_dev; } ;
typedef  enum batadv_nl_commands { ____Placeholder_batadv_nl_commands } batadv_nl_commands ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_ACTIVE ; 
 int /*<<< orphan*/  BATADV_ATTR_ELP_INTERVAL ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFNAME ; 
 int /*<<< orphan*/  BATADV_ATTR_MESH_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_THROUGHPUT_OVERRIDE ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  genl_dump_check_consistent (struct netlink_callback*,void*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_netlink_hardif_fill(struct sk_buff *msg,
				      struct batadv_priv *bat_priv,
				      struct batadv_hard_iface *hard_iface,
				      enum batadv_nl_commands cmd,
				      u32 portid, u32 seq, int flags,
				      struct netlink_callback *cb)
{
	struct net_device *net_dev = hard_iface->net_dev;
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, flags, cmd);
	if (!hdr)
		return -ENOBUFS;

	if (cb)
		genl_dump_check_consistent(cb, hdr);

	if (nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX,
			bat_priv->soft_iface->ifindex))
		goto nla_put_failure;

	if (nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			net_dev->ifindex) ||
	    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   net_dev->name) ||
	    nla_put(msg, BATADV_ATTR_HARD_ADDRESS, ETH_ALEN,
		    net_dev->dev_addr))
		goto nla_put_failure;

	if (hard_iface->if_status == BATADV_IF_ACTIVE) {
		if (nla_put_flag(msg, BATADV_ATTR_ACTIVE))
			goto nla_put_failure;
	}

#ifdef CONFIG_BATMAN_ADV_BATMAN_V
	if (nla_put_u32(msg, BATADV_ATTR_ELP_INTERVAL,
			atomic_read(&hard_iface->bat_v.elp_interval)))
		goto nla_put_failure;

	if (nla_put_u32(msg, BATADV_ATTR_THROUGHPUT_OVERRIDE,
			atomic_read(&hard_iface->bat_v.throughput_override)))
		goto nla_put_failure;
#endif /* CONFIG_BATMAN_ADV_BATMAN_V */

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}