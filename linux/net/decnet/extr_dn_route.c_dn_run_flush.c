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
struct timer_list {int dummy; } ;
struct dn_route {int /*<<< orphan*/  dst; int /*<<< orphan*/  dn_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dn_rt_hash_mask ; 
 TYPE_1__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dst_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct dn_route* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dn_route* xchg (struct dn_route**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_run_flush(struct timer_list *unused)
{
	int i;
	struct dn_route *rt, *next;

	for (i = 0; i < dn_rt_hash_mask; i++) {
		spin_lock_bh(&dn_rt_hash_table[i].lock);

		if ((rt = xchg((struct dn_route **)&dn_rt_hash_table[i].chain, NULL)) == NULL)
			goto nothing_to_declare;

		for(; rt; rt = next) {
			next = rcu_dereference_raw(rt->dn_next);
			RCU_INIT_POINTER(rt->dn_next, NULL);
			dst_dev_put(&rt->dst);
			dst_release(&rt->dst);
		}

nothing_to_declare:
		spin_unlock_bh(&dn_rt_hash_table[i].lock);
	}
}