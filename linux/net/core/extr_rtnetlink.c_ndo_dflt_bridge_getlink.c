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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {scalar_t__ ifindex; scalar_t__ mtu; int /*<<< orphan*/  dev_addr; scalar_t__ addr_len; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  operstate; } ;
struct ifinfomsg {scalar_t__ ifi_index; scalar_t__ ifi_change; int /*<<< orphan*/  ifi_flags; int /*<<< orphan*/  ifi_type; scalar_t__ __ifi_pad; int /*<<< orphan*/  ifi_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BRIDGE ; 
 scalar_t__ BRIDGE_FLAGS_SELF ; 
 scalar_t__ BRIDGE_MODE_UNDEF ; 
 int /*<<< orphan*/  BR_BPDU_GUARD ; 
 int /*<<< orphan*/  BR_FLOOD ; 
 int /*<<< orphan*/  BR_HAIRPIN_MODE ; 
 int /*<<< orphan*/  BR_LEARNING ; 
 int /*<<< orphan*/  BR_LEARNING_SYNC ; 
 int /*<<< orphan*/  BR_MULTICAST_FAST_LEAVE ; 
 int /*<<< orphan*/  BR_PROXYARP ; 
 int /*<<< orphan*/  BR_ROOT_BLOCK ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_ADDRESS ; 
 int /*<<< orphan*/  IFLA_AF_SPEC ; 
 int /*<<< orphan*/  IFLA_BRIDGE_FLAGS ; 
 int /*<<< orphan*/  IFLA_BRIDGE_MODE ; 
 int /*<<< orphan*/  IFLA_BRPORT_FAST_LEAVE ; 
 int /*<<< orphan*/  IFLA_BRPORT_GUARD ; 
 int /*<<< orphan*/  IFLA_BRPORT_LEARNING ; 
 int /*<<< orphan*/  IFLA_BRPORT_LEARNING_SYNC ; 
 int /*<<< orphan*/  IFLA_BRPORT_MODE ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROTECT ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROXYARP ; 
 int /*<<< orphan*/  IFLA_BRPORT_UNICAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_LINK ; 
 int /*<<< orphan*/  IFLA_MASTER ; 
 int /*<<< orphan*/  IFLA_MTU ; 
 int /*<<< orphan*/  IFLA_OPERSTATE ; 
 int /*<<< orphan*/  IFLA_PROTINFO ; 
 int /*<<< orphan*/  IF_OPER_DOWN ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 scalar_t__ brport_nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_flags (struct net_device*) ; 
 scalar_t__ dev_get_iflink (struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int ndo_dflt_bridge_getlink(struct sk_buff *skb, u32 pid, u32 seq,
			    struct net_device *dev, u16 mode,
			    u32 flags, u32 mask, int nlflags,
			    u32 filter_mask,
			    int (*vlan_fill)(struct sk_buff *skb,
					     struct net_device *dev,
					     u32 filter_mask))
{
	struct nlmsghdr *nlh;
	struct ifinfomsg *ifm;
	struct nlattr *br_afspec;
	struct nlattr *protinfo;
	u8 operstate = netif_running(dev) ? dev->operstate : IF_OPER_DOWN;
	struct net_device *br_dev = netdev_master_upper_dev_get(dev);
	int err = 0;

	nlh = nlmsg_put(skb, pid, seq, RTM_NEWLINK, sizeof(*ifm), nlflags);
	if (nlh == NULL)
		return -EMSGSIZE;

	ifm = nlmsg_data(nlh);
	ifm->ifi_family = AF_BRIDGE;
	ifm->__ifi_pad = 0;
	ifm->ifi_type = dev->type;
	ifm->ifi_index = dev->ifindex;
	ifm->ifi_flags = dev_get_flags(dev);
	ifm->ifi_change = 0;


	if (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    nla_put_u8(skb, IFLA_OPERSTATE, operstate) ||
	    (br_dev &&
	     nla_put_u32(skb, IFLA_MASTER, br_dev->ifindex)) ||
	    (dev->addr_len &&
	     nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr)) ||
	    (dev->ifindex != dev_get_iflink(dev) &&
	     nla_put_u32(skb, IFLA_LINK, dev_get_iflink(dev))))
		goto nla_put_failure;

	br_afspec = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
	if (!br_afspec)
		goto nla_put_failure;

	if (nla_put_u16(skb, IFLA_BRIDGE_FLAGS, BRIDGE_FLAGS_SELF)) {
		nla_nest_cancel(skb, br_afspec);
		goto nla_put_failure;
	}

	if (mode != BRIDGE_MODE_UNDEF) {
		if (nla_put_u16(skb, IFLA_BRIDGE_MODE, mode)) {
			nla_nest_cancel(skb, br_afspec);
			goto nla_put_failure;
		}
	}
	if (vlan_fill) {
		err = vlan_fill(skb, dev, filter_mask);
		if (err) {
			nla_nest_cancel(skb, br_afspec);
			goto nla_put_failure;
		}
	}
	nla_nest_end(skb, br_afspec);

	protinfo = nla_nest_start(skb, IFLA_PROTINFO);
	if (!protinfo)
		goto nla_put_failure;

	if (brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_MODE, BR_HAIRPIN_MODE) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_GUARD, BR_BPDU_GUARD) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_FAST_LEAVE,
				BR_MULTICAST_FAST_LEAVE) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_PROTECT, BR_ROOT_BLOCK) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_LEARNING, BR_LEARNING) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_LEARNING_SYNC, BR_LEARNING_SYNC) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_UNICAST_FLOOD, BR_FLOOD) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_PROXYARP, BR_PROXYARP)) {
		nla_nest_cancel(skb, protinfo);
		goto nla_put_failure;
	}

	nla_nest_end(skb, protinfo);

	nlmsg_end(skb, nlh);
	return 0;
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return err ? err : -EMSGSIZE;
}