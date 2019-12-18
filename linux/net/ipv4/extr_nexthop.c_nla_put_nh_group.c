#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nh_group {int num_nh; TYPE_2__* nh_entries; scalar_t__ mpath; } ;
struct nexthop_grp {scalar_t__ weight; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ weight; TYPE_1__* nh; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NEXTHOP_GRP_TYPE_MPATH ; 
 int /*<<< orphan*/  NHA_GROUP ; 
 int /*<<< orphan*/  NHA_GROUP_TYPE ; 
 struct nexthop_grp* nla_data (struct nlattr*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int nla_put_nh_group(struct sk_buff *skb, struct nh_group *nhg)
{
	struct nexthop_grp *p;
	size_t len = nhg->num_nh * sizeof(*p);
	struct nlattr *nla;
	u16 group_type = 0;
	int i;

	if (nhg->mpath)
		group_type = NEXTHOP_GRP_TYPE_MPATH;

	if (nla_put_u16(skb, NHA_GROUP_TYPE, group_type))
		goto nla_put_failure;

	nla = nla_reserve(skb, NHA_GROUP, len);
	if (!nla)
		goto nla_put_failure;

	p = nla_data(nla);
	for (i = 0; i < nhg->num_nh; ++i) {
		p->id = nhg->nh_entries[i].nh->id;
		p->weight = nhg->nh_entries[i].weight - 1;
		p += 1;
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}