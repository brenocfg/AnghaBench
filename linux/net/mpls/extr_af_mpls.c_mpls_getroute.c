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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_flags; int rtm_dst_len; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_table; scalar_t__ rtm_src_len; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct mpls_shim_hdr {int dummy; } ;
struct mpls_route {int /*<<< orphan*/  rt_protocol; } ;
struct mpls_nh {int nh_labels; scalar_t__ nh_via_table; int /*<<< orphan*/  nh_dev; int /*<<< orphan*/  nh_via_alen; int /*<<< orphan*/ * nh_label; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_MPLS ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENETUNREACH ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_P_MPLS_UC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LABEL_NOT_SPECIFIED ; 
 int MAX_NEW_LABELS ; 
 scalar_t__ MPLS_NEIGH_TABLE_UNSPEC ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 size_t RTA_DST ; 
 int /*<<< orphan*/  RTA_MAX ; 
 size_t RTA_NEWDST ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int RTM_F_FIB_MATCH ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lfib_nlmsg_size (struct mpls_route*) ; 
 int mpls_dump_route (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpls_route*,int /*<<< orphan*/ ) ; 
 struct mpls_shim_hdr mpls_entry_encode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct mpls_shim_hdr* mpls_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  mpls_label_ok (struct net*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mpls_nh_via (struct mpls_route*,struct mpls_nh*) ; 
 struct mpls_route* mpls_route_input_rcu (struct net*,int /*<<< orphan*/ ) ; 
 struct mpls_nh* mpls_select_multipath (struct mpls_route*,struct sk_buff*) ; 
 int mpls_valid_getroute_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 scalar_t__ nla_get_labels (struct nlattr*,int,int*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 scalar_t__ nla_put_labels (struct sk_buff*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_via (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_getroute(struct sk_buff *in_skb, struct nlmsghdr *in_nlh,
			 struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	u32 portid = NETLINK_CB(in_skb).portid;
	u32 in_label = LABEL_NOT_SPECIFIED;
	struct nlattr *tb[RTA_MAX + 1];
	u32 labels[MAX_NEW_LABELS];
	struct mpls_shim_hdr *hdr;
	unsigned int hdr_size = 0;
	struct net_device *dev;
	struct mpls_route *rt;
	struct rtmsg *rtm, *r;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	struct mpls_nh *nh;
	u8 n_labels;
	int err;

	err = mpls_valid_getroute_req(in_skb, in_nlh, tb, extack);
	if (err < 0)
		goto errout;

	rtm = nlmsg_data(in_nlh);

	if (tb[RTA_DST]) {
		u8 label_count;

		if (nla_get_labels(tb[RTA_DST], 1, &label_count,
				   &in_label, extack)) {
			err = -EINVAL;
			goto errout;
		}

		if (!mpls_label_ok(net, &in_label, extack)) {
			err = -EINVAL;
			goto errout;
		}
	}

	rt = mpls_route_input_rcu(net, in_label);
	if (!rt) {
		err = -ENETUNREACH;
		goto errout;
	}

	if (rtm->rtm_flags & RTM_F_FIB_MATCH) {
		skb = nlmsg_new(lfib_nlmsg_size(rt), GFP_KERNEL);
		if (!skb) {
			err = -ENOBUFS;
			goto errout;
		}

		err = mpls_dump_route(skb, portid, in_nlh->nlmsg_seq,
				      RTM_NEWROUTE, in_label, rt, 0);
		if (err < 0) {
			/* -EMSGSIZE implies BUG in lfib_nlmsg_size */
			WARN_ON(err == -EMSGSIZE);
			goto errout_free;
		}

		return rtnl_unicast(skb, net, portid);
	}

	if (tb[RTA_NEWDST]) {
		if (nla_get_labels(tb[RTA_NEWDST], MAX_NEW_LABELS, &n_labels,
				   labels, extack) != 0) {
			err = -EINVAL;
			goto errout;
		}

		hdr_size = n_labels * sizeof(struct mpls_shim_hdr);
	}

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb) {
		err = -ENOBUFS;
		goto errout;
	}

	skb->protocol = htons(ETH_P_MPLS_UC);

	if (hdr_size) {
		bool bos;
		int i;

		if (skb_cow(skb, hdr_size)) {
			err = -ENOBUFS;
			goto errout_free;
		}

		skb_reserve(skb, hdr_size);
		skb_push(skb, hdr_size);
		skb_reset_network_header(skb);

		/* Push new labels */
		hdr = mpls_hdr(skb);
		bos = true;
		for (i = n_labels - 1; i >= 0; i--) {
			hdr[i] = mpls_entry_encode(labels[i],
						   1, 0, bos);
			bos = false;
		}
	}

	nh = mpls_select_multipath(rt, skb);
	if (!nh) {
		err = -ENETUNREACH;
		goto errout_free;
	}

	if (hdr_size) {
		skb_pull(skb, hdr_size);
		skb_reset_network_header(skb);
	}

	nlh = nlmsg_put(skb, portid, in_nlh->nlmsg_seq,
			RTM_NEWROUTE, sizeof(*r), 0);
	if (!nlh) {
		err = -EMSGSIZE;
		goto errout_free;
	}

	r = nlmsg_data(nlh);
	r->rtm_family	 = AF_MPLS;
	r->rtm_dst_len	= 20;
	r->rtm_src_len	= 0;
	r->rtm_table	= RT_TABLE_MAIN;
	r->rtm_type	= RTN_UNICAST;
	r->rtm_scope	= RT_SCOPE_UNIVERSE;
	r->rtm_protocol = rt->rt_protocol;
	r->rtm_flags	= 0;

	if (nla_put_labels(skb, RTA_DST, 1, &in_label))
		goto nla_put_failure;

	if (nh->nh_labels &&
	    nla_put_labels(skb, RTA_NEWDST, nh->nh_labels,
			   nh->nh_label))
		goto nla_put_failure;

	if (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC &&
	    nla_put_via(skb, nh->nh_via_table, mpls_nh_via(rt, nh),
			nh->nh_via_alen))
		goto nla_put_failure;
	dev = rtnl_dereference(nh->nh_dev);
	if (dev && nla_put_u32(skb, RTA_OIF, dev->ifindex))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);

	err = rtnl_unicast(skb, net, portid);
errout:
	return err;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	err = -EMSGSIZE;
errout_free:
	kfree_skb(skb);
	return err;
}