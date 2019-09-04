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
struct rtnexthop {int dummy; } ;
struct rtmsg {int dummy; } ;
struct rta_cacheinfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nh_lwtstate; } ;
struct fib6_info {int fib6_nsiblings; TYPE_1__ fib6_nh; } ;

/* Variables and functions */
 int NLA_ALIGN (int) ; 
 size_t NLMSG_ALIGN (int) ; 
 int RTAX_MAX ; 
 int TCP_CA_NAME_MAX ; 
 int lwtunnel_get_encap_size (int /*<<< orphan*/ ) ; 
 int nla_total_size (int) ; 

__attribute__((used)) static size_t rt6_nlmsg_size(struct fib6_info *rt)
{
	int nexthop_len = 0;

	if (rt->fib6_nsiblings) {
		nexthop_len = nla_total_size(0)	 /* RTA_MULTIPATH */
			    + NLA_ALIGN(sizeof(struct rtnexthop))
			    + nla_total_size(16) /* RTA_GATEWAY */
			    + lwtunnel_get_encap_size(rt->fib6_nh.nh_lwtstate);

		nexthop_len *= rt->fib6_nsiblings;
	}

	return NLMSG_ALIGN(sizeof(struct rtmsg))
	       + nla_total_size(16) /* RTA_SRC */
	       + nla_total_size(16) /* RTA_DST */
	       + nla_total_size(16) /* RTA_GATEWAY */
	       + nla_total_size(16) /* RTA_PREFSRC */
	       + nla_total_size(4) /* RTA_TABLE */
	       + nla_total_size(4) /* RTA_IIF */
	       + nla_total_size(4) /* RTA_OIF */
	       + nla_total_size(4) /* RTA_PRIORITY */
	       + RTAX_MAX * nla_total_size(4) /* RTA_METRICS */
	       + nla_total_size(sizeof(struct rta_cacheinfo))
	       + nla_total_size(TCP_CA_NAME_MAX) /* RTAX_CC_ALGO */
	       + nla_total_size(1) /* RTA_PREF */
	       + lwtunnel_get_encap_size(rt->fib6_nh.nh_lwtstate)
	       + nexthop_len;
}