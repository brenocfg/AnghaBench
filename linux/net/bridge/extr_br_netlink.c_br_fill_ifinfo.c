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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {scalar_t__ ifindex; scalar_t__ mtu; int /*<<< orphan*/  dev_addr; scalar_t__ addr_len; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  operstate; } ;
struct net_bridge_vlan_group {int /*<<< orphan*/  num_vlans; } ;
struct net_bridge_port {int flags; struct net_bridge* br; } ;
struct net_bridge {TYPE_1__* dev; } ;
struct ifinfomsg {scalar_t__ ifi_index; scalar_t__ ifi_change; int /*<<< orphan*/  ifi_flags; int /*<<< orphan*/  ifi_type; scalar_t__ __ifi_pad; int /*<<< orphan*/  ifi_family; } ;
struct TYPE_2__ {scalar_t__ ifindex; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BRIDGE ; 
 int BR_VLAN_TUNNEL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_ADDRESS ; 
 int /*<<< orphan*/  IFLA_AF_SPEC ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_LINK ; 
 int /*<<< orphan*/  IFLA_MASTER ; 
 int /*<<< orphan*/  IFLA_MTU ; 
 int /*<<< orphan*/  IFLA_OPERSTATE ; 
 int /*<<< orphan*/  IFLA_PROTINFO ; 
 int /*<<< orphan*/  IF_OPER_DOWN ; 
 int RTEXT_FILTER_BRVLAN ; 
 int RTEXT_FILTER_BRVLAN_COMPRESSED ; 
 int RTM_NEWLINK ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_fill_ifvlaninfo (struct sk_buff*,struct net_bridge_vlan_group*) ; 
 int br_fill_ifvlaninfo_compressed (struct sk_buff*,struct net_bridge_vlan_group*) ; 
 int br_fill_vlan_tunnel_info (struct sk_buff*,struct net_bridge_vlan_group*) ; 
 scalar_t__ br_port_fill_attrs (struct sk_buff*,struct net_bridge_port const*) ; 
 struct net_bridge_vlan_group* br_vlan_group_rcu (struct net_bridge*) ; 
 int /*<<< orphan*/  dev_get_flags (struct net_device const*) ; 
 scalar_t__ dev_get_iflink (struct net_device const*) ; 
 struct net_bridge_vlan_group* nbp_vlan_group_rcu (struct net_bridge_port const*) ; 
 struct net_bridge* netdev_priv (struct net_device const*) ; 
 scalar_t__ netif_running (struct net_device const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int br_fill_ifinfo(struct sk_buff *skb,
			  const struct net_bridge_port *port,
			  u32 pid, u32 seq, int event, unsigned int flags,
			  u32 filter_mask, const struct net_device *dev)
{
	u8 operstate = netif_running(dev) ? dev->operstate : IF_OPER_DOWN;
	struct net_bridge *br;
	struct ifinfomsg *hdr;
	struct nlmsghdr *nlh;

	if (port)
		br = port->br;
	else
		br = netdev_priv(dev);

	br_debug(br, "br_fill_info event %d port %s master %s\n",
		     event, dev->name, br->dev->name);

	nlh = nlmsg_put(skb, pid, seq, event, sizeof(*hdr), flags);
	if (nlh == NULL)
		return -EMSGSIZE;

	hdr = nlmsg_data(nlh);
	hdr->ifi_family = AF_BRIDGE;
	hdr->__ifi_pad = 0;
	hdr->ifi_type = dev->type;
	hdr->ifi_index = dev->ifindex;
	hdr->ifi_flags = dev_get_flags(dev);
	hdr->ifi_change = 0;

	if (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    nla_put_u32(skb, IFLA_MASTER, br->dev->ifindex) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    nla_put_u8(skb, IFLA_OPERSTATE, operstate) ||
	    (dev->addr_len &&
	     nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr)) ||
	    (dev->ifindex != dev_get_iflink(dev) &&
	     nla_put_u32(skb, IFLA_LINK, dev_get_iflink(dev))))
		goto nla_put_failure;

	if (event == RTM_NEWLINK && port) {
		struct nlattr *nest;

		nest = nla_nest_start(skb, IFLA_PROTINFO);
		if (nest == NULL || br_port_fill_attrs(skb, port) < 0)
			goto nla_put_failure;
		nla_nest_end(skb, nest);
	}

	/* Check if  the VID information is requested */
	if ((filter_mask & RTEXT_FILTER_BRVLAN) ||
	    (filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED)) {
		struct net_bridge_vlan_group *vg;
		struct nlattr *af;
		int err;

		/* RCU needed because of the VLAN locking rules (rcu || rtnl) */
		rcu_read_lock();
		if (port)
			vg = nbp_vlan_group_rcu(port);
		else
			vg = br_vlan_group_rcu(br);

		if (!vg || !vg->num_vlans) {
			rcu_read_unlock();
			goto done;
		}
		af = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
		if (!af) {
			rcu_read_unlock();
			goto nla_put_failure;
		}
		if (filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED)
			err = br_fill_ifvlaninfo_compressed(skb, vg);
		else
			err = br_fill_ifvlaninfo(skb, vg);

		if (port && (port->flags & BR_VLAN_TUNNEL))
			err = br_fill_vlan_tunnel_info(skb, vg);
		rcu_read_unlock();
		if (err)
			goto nla_put_failure;
		nla_nest_end(skb, af);
	}

done:
	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}