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
struct nh_group {int num_nh; TYPE_1__* nh_entries; } ;
struct nexthop {int /*<<< orphan*/  nh_grp; } ;
struct TYPE_2__ {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nh_group*) ; 
 struct nh_group* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nexthop_free_mpath(struct nexthop *nh)
{
	struct nh_group *nhg;
	int i;

	nhg = rcu_dereference_raw(nh->nh_grp);
	for (i = 0; i < nhg->num_nh; ++i)
		WARN_ON(nhg->nh_entries[i].nh);

	kfree(nhg);
}