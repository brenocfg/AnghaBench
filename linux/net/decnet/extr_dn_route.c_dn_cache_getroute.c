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
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_flags; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  dn_ptr; } ;
struct net {int dummy; } ;
struct flowidn {void* flowidn_oif; void* daddr; void* dst; void* saddr; void* src; void* flowidn_iif; int /*<<< orphan*/  flowidn_proto; } ;
struct dst_entry {int dummy; } ;
struct dn_skb_cb {void* flowidn_oif; void* daddr; void* dst; void* saddr; void* src; void* flowidn_iif; int /*<<< orphan*/  flowidn_proto; } ;
struct TYPE_3__ {int error; } ;
struct dn_route {int /*<<< orphan*/  rt_flags; TYPE_1__ dst; } ;
typedef  int /*<<< orphan*/  fld ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNPROTO_NSP ; 
 struct flowidn* DN_SKB_CB (struct sk_buff*) ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETH_P_DNA_RT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 size_t RTA_DST ; 
 size_t RTA_IIF ; 
 int /*<<< orphan*/  RTA_MAX ; 
 size_t RTA_OIF ; 
 size_t RTA_SRC ; 
 int /*<<< orphan*/  RTCF_NOTIFY ; 
 int RTM_F_NOTIFY ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,void*) ; 
 int dn_route_input (struct sk_buff*) ; 
 int dn_route_output_key (struct dst_entry**,struct flowidn*,int /*<<< orphan*/ ) ; 
 int dn_rt_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memset (struct flowidn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 void* nla_get_le16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_dn_policy ; 
 int rtnl_unicast (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_1__*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_cache_getroute(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct rtmsg *rtm = nlmsg_data(nlh);
	struct dn_route *rt = NULL;
	struct dn_skb_cb *cb;
	int err;
	struct sk_buff *skb;
	struct flowidn fld;
	struct nlattr *tb[RTA_MAX+1];

	if (!net_eq(net, &init_net))
		return -EINVAL;

	err = nlmsg_parse_deprecated(nlh, sizeof(*rtm), tb, RTA_MAX,
				     rtm_dn_policy, extack);
	if (err < 0)
		return err;

	memset(&fld, 0, sizeof(fld));
	fld.flowidn_proto = DNPROTO_NSP;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb == NULL)
		return -ENOBUFS;
	skb_reset_mac_header(skb);
	cb = DN_SKB_CB(skb);

	if (tb[RTA_SRC])
		fld.saddr = nla_get_le16(tb[RTA_SRC]);

	if (tb[RTA_DST])
		fld.daddr = nla_get_le16(tb[RTA_DST]);

	if (tb[RTA_IIF])
		fld.flowidn_iif = nla_get_u32(tb[RTA_IIF]);

	if (fld.flowidn_iif) {
		struct net_device *dev;
		dev = __dev_get_by_index(&init_net, fld.flowidn_iif);
		if (!dev || !dev->dn_ptr) {
			kfree_skb(skb);
			return -ENODEV;
		}
		skb->protocol = htons(ETH_P_DNA_RT);
		skb->dev = dev;
		cb->src = fld.saddr;
		cb->dst = fld.daddr;
		local_bh_disable();
		err = dn_route_input(skb);
		local_bh_enable();
		memset(cb, 0, sizeof(struct dn_skb_cb));
		rt = (struct dn_route *)skb_dst(skb);
		if (!err && -rt->dst.error)
			err = rt->dst.error;
	} else {
		if (tb[RTA_OIF])
			fld.flowidn_oif = nla_get_u32(tb[RTA_OIF]);

		err = dn_route_output_key((struct dst_entry **)&rt, &fld, 0);
	}

	skb->dev = NULL;
	if (err)
		goto out_free;
	skb_dst_set(skb, &rt->dst);
	if (rtm->rtm_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	err = dn_rt_fill_info(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq, RTM_NEWROUTE, 0, 0);
	if (err < 0) {
		err = -EMSGSIZE;
		goto out_free;
	}

	return rtnl_unicast(skb, &init_net, NETLINK_CB(in_skb).portid);

out_free:
	kfree_skb(skb);
	return err;
}