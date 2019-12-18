#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nhc_lwtstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  fib_nh_gw_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  fib_nh_gw_family; } ;
struct nh_info {int family; TYPE_1__ fib_nhc; TYPE_3__ fib6_nh; TYPE_2__ fib_nh; } ;
struct nexthop {int /*<<< orphan*/  nh_info; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ lwtunnel_get_encap_size (scalar_t__) ; 
 size_t nla_total_size (int) ; 
 struct nh_info* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t nh_nlmsg_size_single(struct nexthop *nh)
{
	struct nh_info *nhi = rtnl_dereference(nh->nh_info);
	size_t sz;

	/* covers NHA_BLACKHOLE since NHA_OIF and BLACKHOLE
	 * are mutually exclusive
	 */
	sz = nla_total_size(4);  /* NHA_OIF */

	switch (nhi->family) {
	case AF_INET:
		if (nhi->fib_nh.fib_nh_gw_family)
			sz += nla_total_size(4);  /* NHA_GATEWAY */
		break;

	case AF_INET6:
		/* NHA_GATEWAY */
		if (nhi->fib6_nh.fib_nh_gw_family)
			sz += nla_total_size(sizeof(const struct in6_addr));
		break;
	}

	if (nhi->fib_nhc.nhc_lwtstate) {
		sz += lwtunnel_get_encap_size(nhi->fib_nhc.nhc_lwtstate);
		sz += nla_total_size(2);  /* NHA_ENCAP_TYPE */
	}

	return sz;
}