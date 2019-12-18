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
struct nh_info {scalar_t__ family; } ;
struct nh_group {scalar_t__ has_v4; } ;
struct nexthop {int /*<<< orphan*/  nh_info; int /*<<< orphan*/  nh_grp; scalar_t__ is_group; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_src; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ check_src_addr (int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

int fib6_check_nexthop(struct nexthop *nh, struct fib6_config *cfg,
		       struct netlink_ext_ack *extack)
{
	struct nh_info *nhi;

	/* fib6_src is unique to a fib6_info and limits the ability to cache
	 * routes in fib6_nh within a nexthop that is potentially shared
	 * across multiple fib entries. If the config wants to use source
	 * routing it can not use nexthop objects. mlxsw also does not allow
	 * fib6_src on routes.
	 */
	if (cfg && check_src_addr(&cfg->fc_src, extack) < 0)
		return -EINVAL;

	if (nh->is_group) {
		struct nh_group *nhg;

		nhg = rtnl_dereference(nh->nh_grp);
		if (nhg->has_v4)
			goto no_v4_nh;
	} else {
		nhi = rtnl_dereference(nh->nh_info);
		if (nhi->family == AF_INET)
			goto no_v4_nh;
	}

	return 0;
no_v4_nh:
	NL_SET_ERR_MSG(extack, "IPv6 routes can not use an IPv4 nexthop");
	return -EINVAL;
}