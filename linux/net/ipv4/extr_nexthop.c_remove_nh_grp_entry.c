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
struct nh_grp_entry {int /*<<< orphan*/  nh_parent; struct nexthop* nh; int /*<<< orphan*/  nh_list; int /*<<< orphan*/  weight; } ;
struct nh_group {int num_nh; struct nh_grp_entry* nh_entries; } ;
struct nexthop {int /*<<< orphan*/  grp_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_NEWNEXTHOP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nexthop_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nl_info*) ; 
 int /*<<< orphan*/  nexthop_put (struct nexthop*) ; 
 int /*<<< orphan*/  nh_group_rebalance (struct nh_group*) ; 

__attribute__((used)) static void remove_nh_grp_entry(struct nh_grp_entry *nhge,
				struct nh_group *nhg,
				struct nl_info *nlinfo)
{
	struct nexthop *nh = nhge->nh;
	struct nh_grp_entry *nhges;
	bool found = false;
	int i;

	WARN_ON(!nh);

	nhges = nhg->nh_entries;
	for (i = 0; i < nhg->num_nh; ++i) {
		if (found) {
			nhges[i-1].nh = nhges[i].nh;
			nhges[i-1].weight = nhges[i].weight;
			list_del(&nhges[i].nh_list);
			list_add(&nhges[i-1].nh_list, &nhges[i-1].nh->grp_list);
		} else if (nhg->nh_entries[i].nh == nh) {
			found = true;
		}
	}

	if (WARN_ON(!found))
		return;

	nhg->num_nh--;
	nhg->nh_entries[nhg->num_nh].nh = NULL;

	nh_group_rebalance(nhg);

	nexthop_put(nh);

	if (nlinfo)
		nexthop_notify(RTM_NEWNEXTHOP, nhge->nh_parent, nlinfo);
}