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
typedef  int /*<<< orphan*/  u8 ;
struct nh_group {TYPE_1__* nh_entries; } ;
struct nexthop {int /*<<< orphan*/  nh_grp; scalar_t__ is_group; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {struct nexthop* nh; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 int nexthop_check_scope (struct nexthop*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct nh_group* rtnl_dereference (int /*<<< orphan*/ ) ; 

int fib_check_nexthop(struct nexthop *nh, u8 scope,
		      struct netlink_ext_ack *extack)
{
	int err = 0;

	if (nh->is_group) {
		struct nh_group *nhg;

		if (scope == RT_SCOPE_HOST) {
			NL_SET_ERR_MSG(extack, "Route with host scope can not have multiple nexthops");
			err = -EINVAL;
			goto out;
		}

		nhg = rtnl_dereference(nh->nh_grp);
		/* all nexthops in a group have the same scope */
		err = nexthop_check_scope(nhg->nh_entries[0].nh, scope, extack);
	} else {
		err = nexthop_check_scope(nh, scope, extack);
	}
out:
	return err;
}