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
struct netlink_ext_ack {int dummy; } ;
struct fib_info {scalar_t__ fib_priority; TYPE_1__* fib_nh; } ;
struct fib_config {scalar_t__ fc_priority; scalar_t__ fc_oif; scalar_t__ fc_gw; scalar_t__ fc_encap; int /*<<< orphan*/  fc_encap_type; } ;
struct TYPE_2__ {scalar_t__ nh_oif; scalar_t__ nh_gw; } ;

/* Variables and functions */
 scalar_t__ fib_encap_match (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,struct fib_config*,struct netlink_ext_ack*) ; 

int fib_nh_match(struct fib_config *cfg, struct fib_info *fi,
		 struct netlink_ext_ack *extack)
{
#ifdef CONFIG_IP_ROUTE_MULTIPATH
	struct rtnexthop *rtnh;
	int remaining;
#endif

	if (cfg->fc_priority && cfg->fc_priority != fi->fib_priority)
		return 1;

	if (cfg->fc_oif || cfg->fc_gw) {
		if (cfg->fc_encap) {
			if (fib_encap_match(cfg->fc_encap_type, cfg->fc_encap,
					    fi->fib_nh, cfg, extack))
				return 1;
		}
#ifdef CONFIG_IP_ROUTE_CLASSID
		if (cfg->fc_flow &&
		    cfg->fc_flow != fi->fib_nh->nh_tclassid)
			return 1;
#endif
		if ((!cfg->fc_oif || cfg->fc_oif == fi->fib_nh->nh_oif) &&
		    (!cfg->fc_gw  || cfg->fc_gw == fi->fib_nh->nh_gw))
			return 0;
		return 1;
	}

#ifdef CONFIG_IP_ROUTE_MULTIPATH
	if (!cfg->fc_mp)
		return 0;

	rtnh = cfg->fc_mp;
	remaining = cfg->fc_mp_len;

	for_nexthops(fi) {
		int attrlen;

		if (!rtnh_ok(rtnh, remaining))
			return -EINVAL;

		if (rtnh->rtnh_ifindex && rtnh->rtnh_ifindex != nh->nh_oif)
			return 1;

		attrlen = rtnh_attrlen(rtnh);
		if (attrlen > 0) {
			struct nlattr *nla, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			if (nla && nla_get_in_addr(nla) != nh->nh_gw)
				return 1;
#ifdef CONFIG_IP_ROUTE_CLASSID
			nla = nla_find(attrs, attrlen, RTA_FLOW);
			if (nla && nla_get_u32(nla) != nh->nh_tclassid)
				return 1;
#endif
		}

		rtnh = rtnh_next(rtnh, &remaining);
	} endfor_nexthops(fi);
#endif
	return 0;
}