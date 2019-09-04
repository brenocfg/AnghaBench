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
typedef  void* u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct rtmsg {int rtm_dst_len; int rtm_table; int rtm_flags; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; void* rtm_type; void* rtm_tos; scalar_t__ rtm_src_len; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int dummy; } ;
struct in_device {int dummy; } ;
struct fib_info {int fib_flags; int fib_priority; int fib_nhs; TYPE_2__* fib_nh; scalar_t__ fib_prefsrc; TYPE_1__* fib_metrics; int /*<<< orphan*/  fib_protocol; int /*<<< orphan*/  fib_scope; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int nh_oif; int nh_flags; scalar_t__ nh_lwtstate; int /*<<< orphan*/  nh_dev; scalar_t__ nh_gw; } ;
struct TYPE_3__ {int /*<<< orphan*/  metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EMSGSIZE ; 
 scalar_t__ IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN (struct in_device*) ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int /*<<< orphan*/  RTA_PREFSRC ; 
 int /*<<< orphan*/  RTA_PRIORITY ; 
 int /*<<< orphan*/  RTA_TABLE ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 int RTNH_F_OFFLOAD ; 
 int RT_TABLE_COMPAT ; 
 struct in_device* __in_dev_get_rcu (int /*<<< orphan*/ ) ; 
 scalar_t__ lwtunnel_fill_encap (struct sk_buff*,scalar_t__) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rtnetlink_put_metrics (struct sk_buff*,int /*<<< orphan*/ ) ; 

int fib_dump_info(struct sk_buff *skb, u32 portid, u32 seq, int event,
		  u32 tb_id, u8 type, __be32 dst, int dst_len, u8 tos,
		  struct fib_info *fi, unsigned int flags)
{
	struct nlmsghdr *nlh;
	struct rtmsg *rtm;

	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*rtm), flags);
	if (!nlh)
		return -EMSGSIZE;

	rtm = nlmsg_data(nlh);
	rtm->rtm_family = AF_INET;
	rtm->rtm_dst_len = dst_len;
	rtm->rtm_src_len = 0;
	rtm->rtm_tos = tos;
	if (tb_id < 256)
		rtm->rtm_table = tb_id;
	else
		rtm->rtm_table = RT_TABLE_COMPAT;
	if (nla_put_u32(skb, RTA_TABLE, tb_id))
		goto nla_put_failure;
	rtm->rtm_type = type;
	rtm->rtm_flags = fi->fib_flags;
	rtm->rtm_scope = fi->fib_scope;
	rtm->rtm_protocol = fi->fib_protocol;

	if (rtm->rtm_dst_len &&
	    nla_put_in_addr(skb, RTA_DST, dst))
		goto nla_put_failure;
	if (fi->fib_priority &&
	    nla_put_u32(skb, RTA_PRIORITY, fi->fib_priority))
		goto nla_put_failure;
	if (rtnetlink_put_metrics(skb, fi->fib_metrics->metrics) < 0)
		goto nla_put_failure;

	if (fi->fib_prefsrc &&
	    nla_put_in_addr(skb, RTA_PREFSRC, fi->fib_prefsrc))
		goto nla_put_failure;
	if (fi->fib_nhs == 1) {
		if (fi->fib_nh->nh_gw &&
		    nla_put_in_addr(skb, RTA_GATEWAY, fi->fib_nh->nh_gw))
			goto nla_put_failure;
		if (fi->fib_nh->nh_oif &&
		    nla_put_u32(skb, RTA_OIF, fi->fib_nh->nh_oif))
			goto nla_put_failure;
		if (fi->fib_nh->nh_flags & RTNH_F_LINKDOWN) {
			struct in_device *in_dev;

			rcu_read_lock();
			in_dev = __in_dev_get_rcu(fi->fib_nh->nh_dev);
			if (in_dev &&
			    IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev))
				rtm->rtm_flags |= RTNH_F_DEAD;
			rcu_read_unlock();
		}
		if (fi->fib_nh->nh_flags & RTNH_F_OFFLOAD)
			rtm->rtm_flags |= RTNH_F_OFFLOAD;
#ifdef CONFIG_IP_ROUTE_CLASSID
		if (fi->fib_nh[0].nh_tclassid &&
		    nla_put_u32(skb, RTA_FLOW, fi->fib_nh[0].nh_tclassid))
			goto nla_put_failure;
#endif
		if (fi->fib_nh->nh_lwtstate &&
		    lwtunnel_fill_encap(skb, fi->fib_nh->nh_lwtstate) < 0)
			goto nla_put_failure;
	}
#ifdef CONFIG_IP_ROUTE_MULTIPATH
	if (fi->fib_nhs > 1) {
		struct rtnexthop *rtnh;
		struct nlattr *mp;

		mp = nla_nest_start(skb, RTA_MULTIPATH);
		if (!mp)
			goto nla_put_failure;

		for_nexthops(fi) {
			rtnh = nla_reserve_nohdr(skb, sizeof(*rtnh));
			if (!rtnh)
				goto nla_put_failure;

			rtnh->rtnh_flags = nh->nh_flags & 0xFF;
			if (nh->nh_flags & RTNH_F_LINKDOWN) {
				struct in_device *in_dev;

				rcu_read_lock();
				in_dev = __in_dev_get_rcu(nh->nh_dev);
				if (in_dev &&
				    IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev))
					rtnh->rtnh_flags |= RTNH_F_DEAD;
				rcu_read_unlock();
			}
			rtnh->rtnh_hops = nh->nh_weight - 1;
			rtnh->rtnh_ifindex = nh->nh_oif;

			if (nh->nh_gw &&
			    nla_put_in_addr(skb, RTA_GATEWAY, nh->nh_gw))
				goto nla_put_failure;
#ifdef CONFIG_IP_ROUTE_CLASSID
			if (nh->nh_tclassid &&
			    nla_put_u32(skb, RTA_FLOW, nh->nh_tclassid))
				goto nla_put_failure;
#endif
			if (nh->nh_lwtstate &&
			    lwtunnel_fill_encap(skb, nh->nh_lwtstate) < 0)
				goto nla_put_failure;

			/* length of rtnetlink header + attributes */
			rtnh->rtnh_len = nlmsg_get_pos(skb) - (void *) rtnh;
		} endfor_nexthops(fi);

		nla_nest_end(skb, mp);
	}
#endif
	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}