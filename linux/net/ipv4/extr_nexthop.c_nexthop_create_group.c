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
struct nlattr {int dummy; } ;
struct nh_info {scalar_t__ family; } ;
struct nh_group {int is_group; int num_nh; int has_v4; int mpath; TYPE_1__* nh_entries; int /*<<< orphan*/  nh_grp; int /*<<< orphan*/  grp_list; int /*<<< orphan*/  nh_info; } ;
struct nh_config {scalar_t__ nh_grp_type; struct nlattr* nh_grp; } ;
struct nexthop_grp {scalar_t__ weight; int /*<<< orphan*/  id; } ;
struct nexthop {int is_group; int num_nh; int has_v4; int mpath; TYPE_1__* nh_entries; int /*<<< orphan*/  nh_grp; int /*<<< orphan*/  grp_list; int /*<<< orphan*/  nh_info; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct nh_group* nh; struct nh_group* nh_parent; int /*<<< orphan*/  nh_list; scalar_t__ weight; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nh_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXTHOP_GRP_TYPE_MPATH ; 
 int /*<<< orphan*/  kfree (struct nh_group*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nh_group* nexthop_alloc () ; 
 struct nh_group* nexthop_find_by_id (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexthop_get (struct nh_group*) ; 
 struct nh_group* nexthop_grp_alloc (int) ; 
 int /*<<< orphan*/  nexthop_put (struct nh_group*) ; 
 int /*<<< orphan*/  nh_group_rebalance (struct nh_group*) ; 
 struct nexthop_grp* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nh_group*) ; 
 struct nh_info* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nexthop *nexthop_create_group(struct net *net,
					    struct nh_config *cfg)
{
	struct nlattr *grps_attr = cfg->nh_grp;
	struct nexthop_grp *entry = nla_data(grps_attr);
	struct nh_group *nhg;
	struct nexthop *nh;
	int i;

	nh = nexthop_alloc();
	if (!nh)
		return ERR_PTR(-ENOMEM);

	nh->is_group = 1;

	nhg = nexthop_grp_alloc(nla_len(grps_attr) / sizeof(*entry));
	if (!nhg) {
		kfree(nh);
		return ERR_PTR(-ENOMEM);
	}

	for (i = 0; i < nhg->num_nh; ++i) {
		struct nexthop *nhe;
		struct nh_info *nhi;

		nhe = nexthop_find_by_id(net, entry[i].id);
		if (!nexthop_get(nhe))
			goto out_no_nh;

		nhi = rtnl_dereference(nhe->nh_info);
		if (nhi->family == AF_INET)
			nhg->has_v4 = true;

		nhg->nh_entries[i].nh = nhe;
		nhg->nh_entries[i].weight = entry[i].weight + 1;
		list_add(&nhg->nh_entries[i].nh_list, &nhe->grp_list);
		nhg->nh_entries[i].nh_parent = nh;
	}

	if (cfg->nh_grp_type == NEXTHOP_GRP_TYPE_MPATH) {
		nhg->mpath = 1;
		nh_group_rebalance(nhg);
	}

	rcu_assign_pointer(nh->nh_grp, nhg);

	return nh;

out_no_nh:
	for (; i >= 0; --i)
		nexthop_put(nhg->nh_entries[i].nh);

	kfree(nhg);
	kfree(nh);

	return ERR_PTR(-ENOENT);
}