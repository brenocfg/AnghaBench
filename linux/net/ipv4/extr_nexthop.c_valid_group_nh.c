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
struct nh_info {scalar_t__ reject_nh; } ;
struct nh_group {scalar_t__ mpath; } ;
struct nexthop {int /*<<< orphan*/  nh_info; int /*<<< orphan*/  nh_grp; scalar_t__ is_group; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool valid_group_nh(struct nexthop *nh, unsigned int npaths,
			   struct netlink_ext_ack *extack)
{
	if (nh->is_group) {
		struct nh_group *nhg = rtnl_dereference(nh->nh_grp);

		/* nested multipath (group within a group) is not
		 * supported
		 */
		if (nhg->mpath) {
			NL_SET_ERR_MSG(extack,
				       "Multipath group can not be a nexthop within a group");
			return false;
		}
	} else {
		struct nh_info *nhi = rtnl_dereference(nh->nh_info);

		if (nhi->reject_nh && npaths > 1) {
			NL_SET_ERR_MSG(extack,
				       "Blackhole nexthop can not be used in a group with more than 1 path");
			return false;
		}
	}

	return true;
}