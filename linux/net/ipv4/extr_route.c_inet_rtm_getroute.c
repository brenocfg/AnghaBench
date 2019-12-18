#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int mark; struct net_device* dev; int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_flags; int /*<<< orphan*/  rtm_tos; } ;
struct TYPE_6__ {int error; } ;
struct rtable {int /*<<< orphan*/  rt_type; int /*<<< orphan*/  rt_flags; TYPE_2__ dst; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {struct net_device* loopback_dev; } ;
struct flowi4 {int flowi4_mark; int flowi4_iif; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_proto; void* fl4_dport; void* fl4_sport; int /*<<< orphan*/  flowi4_uid; void* flowi4_oif; void* saddr; void* daddr; } ;
struct fib_result {size_t type; int /*<<< orphan*/  fi; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  prefix; TYPE_1__* table; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  void* __be32 ;
typedef  void* __be16 ;
struct TYPE_8__ {int /*<<< orphan*/  portid; } ;
struct TYPE_7__ {int error; } ;
struct TYPE_5__ {int tb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EHOSTUNREACH ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int LOOPBACK_IFINDEX ; 
 TYPE_4__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct rtable*) ; 
 size_t RTA_DPORT ; 
 size_t RTA_DST ; 
 size_t RTA_IIF ; 
 size_t RTA_IP_PROTO ; 
 size_t RTA_MARK ; 
 int /*<<< orphan*/  RTA_MAX ; 
 size_t RTA_OIF ; 
 size_t RTA_SPORT ; 
 size_t RTA_SRC ; 
 size_t RTA_UID ; 
 int /*<<< orphan*/  RTCF_NOTIFY ; 
 int RTM_F_FIB_MATCH ; 
 int RTM_F_LOOKUP_TABLE ; 
 int RTM_F_NOTIFY ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int RT_TABLE_MAIN ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int fib_dump_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* fib_props ; 
 struct sk_buff* inet_rtm_getroute_build_skb (void*,void*,int /*<<< orphan*/ ,void*,void*) ; 
 int inet_rtm_valid_getroute_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 int ip_route_input_rcu (struct sk_buff*,void*,void*,int /*<<< orphan*/ ,struct net_device*,struct fib_result*) ; 
 struct rtable* ip_route_output_key_hash_rcu (struct net*,struct flowi4*,struct fib_result*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,void*) ; 
 void* nla_get_be16 (struct nlattr*) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rt_fill_info (struct net*,void*,void*,struct rtable*,int,struct flowi4*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtm_getroute_parse_ip_proto (struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_rtm_getroute(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct nlattr *tb[RTA_MAX+1];
	u32 table_id = RT_TABLE_MAIN;
	__be16 sport = 0, dport = 0;
	struct fib_result res = {};
	u8 ip_proto = IPPROTO_UDP;
	struct rtable *rt = NULL;
	struct sk_buff *skb;
	struct rtmsg *rtm;
	struct flowi4 fl4 = {};
	__be32 dst = 0;
	__be32 src = 0;
	kuid_t uid;
	u32 iif;
	int err;
	int mark;

	err = inet_rtm_valid_getroute_req(in_skb, nlh, tb, extack);
	if (err < 0)
		return err;

	rtm = nlmsg_data(nlh);
	src = tb[RTA_SRC] ? nla_get_in_addr(tb[RTA_SRC]) : 0;
	dst = tb[RTA_DST] ? nla_get_in_addr(tb[RTA_DST]) : 0;
	iif = tb[RTA_IIF] ? nla_get_u32(tb[RTA_IIF]) : 0;
	mark = tb[RTA_MARK] ? nla_get_u32(tb[RTA_MARK]) : 0;
	if (tb[RTA_UID])
		uid = make_kuid(current_user_ns(), nla_get_u32(tb[RTA_UID]));
	else
		uid = (iif ? INVALID_UID : current_uid());

	if (tb[RTA_IP_PROTO]) {
		err = rtm_getroute_parse_ip_proto(tb[RTA_IP_PROTO],
						  &ip_proto, AF_INET, extack);
		if (err)
			return err;
	}

	if (tb[RTA_SPORT])
		sport = nla_get_be16(tb[RTA_SPORT]);

	if (tb[RTA_DPORT])
		dport = nla_get_be16(tb[RTA_DPORT]);

	skb = inet_rtm_getroute_build_skb(src, dst, ip_proto, sport, dport);
	if (!skb)
		return -ENOBUFS;

	fl4.daddr = dst;
	fl4.saddr = src;
	fl4.flowi4_tos = rtm->rtm_tos;
	fl4.flowi4_oif = tb[RTA_OIF] ? nla_get_u32(tb[RTA_OIF]) : 0;
	fl4.flowi4_mark = mark;
	fl4.flowi4_uid = uid;
	if (sport)
		fl4.fl4_sport = sport;
	if (dport)
		fl4.fl4_dport = dport;
	fl4.flowi4_proto = ip_proto;

	rcu_read_lock();

	if (iif) {
		struct net_device *dev;

		dev = dev_get_by_index_rcu(net, iif);
		if (!dev) {
			err = -ENODEV;
			goto errout_rcu;
		}

		fl4.flowi4_iif = iif; /* for rt_fill_info */
		skb->dev	= dev;
		skb->mark	= mark;
		err = ip_route_input_rcu(skb, dst, src, rtm->rtm_tos,
					 dev, &res);

		rt = skb_rtable(skb);
		if (err == 0 && rt->dst.error)
			err = -rt->dst.error;
	} else {
		fl4.flowi4_iif = LOOPBACK_IFINDEX;
		skb->dev = net->loopback_dev;
		rt = ip_route_output_key_hash_rcu(net, &fl4, &res, skb);
		err = 0;
		if (IS_ERR(rt))
			err = PTR_ERR(rt);
		else
			skb_dst_set(skb, &rt->dst);
	}

	if (err)
		goto errout_rcu;

	if (rtm->rtm_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	if (rtm->rtm_flags & RTM_F_LOOKUP_TABLE)
		table_id = res.table ? res.table->tb_id : 0;

	/* reset skb for netlink reply msg */
	skb_trim(skb, 0);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_mac_header(skb);

	if (rtm->rtm_flags & RTM_F_FIB_MATCH) {
		if (!res.fi) {
			err = fib_props[res.type].error;
			if (!err)
				err = -EHOSTUNREACH;
			goto errout_rcu;
		}
		err = fib_dump_info(skb, NETLINK_CB(in_skb).portid,
				    nlh->nlmsg_seq, RTM_NEWROUTE, table_id,
				    rt->rt_type, res.prefix, res.prefixlen,
				    fl4.flowi4_tos, res.fi, 0);
	} else {
		err = rt_fill_info(net, dst, src, rt, table_id, &fl4, skb,
				   NETLINK_CB(in_skb).portid,
				   nlh->nlmsg_seq, 0);
	}
	if (err < 0)
		goto errout_rcu;

	rcu_read_unlock();

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);

errout_free:
	return err;
errout_rcu:
	rcu_read_unlock();
	kfree_skb(skb);
	goto errout_free;
}