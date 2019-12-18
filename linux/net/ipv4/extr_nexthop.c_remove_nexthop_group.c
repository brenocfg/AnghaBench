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
struct nl_info {int dummy; } ;
struct nh_grp_entry {int /*<<< orphan*/ * nh; int /*<<< orphan*/  nh_list; } ;
struct nh_group {int num_nh; struct nh_grp_entry* nh_entries; } ;
struct nexthop {int /*<<< orphan*/  nh_grp; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nexthop_put (int /*<<< orphan*/ *) ; 
 struct nh_group* rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_nexthop_group(struct nexthop *nh, struct nl_info *nlinfo)
{
	struct nh_group *nhg = rcu_dereference_rtnl(nh->nh_grp);
	int i, num_nh = nhg->num_nh;

	for (i = 0; i < num_nh; ++i) {
		struct nh_grp_entry *nhge = &nhg->nh_entries[i];

		if (WARN_ON(!nhge->nh))
			continue;

		list_del(&nhge->nh_list);
		nexthop_put(nhge->nh);
		nhge->nh = NULL;
		nhg->num_nh--;
	}
}