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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int nhc_flags; scalar_t__ nhc_gw_family; } ;
struct nh_info {TYPE_1__ fib_nhc; } ;
struct nexthop {int /*<<< orphan*/  nh_info; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTNH_F_ONLINK ; 
 scalar_t__ RT_SCOPE_HOST ; 
 scalar_t__ RT_SCOPE_LINK ; 
 struct nh_info* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nexthop_check_scope(struct nexthop *nh, u8 scope,
			       struct netlink_ext_ack *extack)
{
	struct nh_info *nhi;

	nhi = rtnl_dereference(nh->nh_info);
	if (scope == RT_SCOPE_HOST && nhi->fib_nhc.nhc_gw_family) {
		NL_SET_ERR_MSG(extack,
			       "Route with host scope can not have a gateway");
		return -EINVAL;
	}

	if (nhi->fib_nhc.nhc_flags & RTNH_F_ONLINK && scope >= RT_SCOPE_LINK) {
		NL_SET_ERR_MSG(extack, "Scope mismatch with nexthop");
		return -EINVAL;
	}

	return 0;
}