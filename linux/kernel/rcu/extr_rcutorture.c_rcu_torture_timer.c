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
struct rcu_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* call ) (struct rcu_head*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* cur_ops ; 
 struct rcu_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_rcu_torture_timers ; 
 int /*<<< orphan*/  rcu_torture_one_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_torture_timer_cb ; 
 int /*<<< orphan*/  rcu_torture_timer_rand ; 
 int /*<<< orphan*/  stub1 (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_torture_timer(struct timer_list *unused)
{
	atomic_long_inc(&n_rcu_torture_timers);
	(void)rcu_torture_one_read(this_cpu_ptr(&rcu_torture_timer_rand));

	/* Test call_rcu() invocation from interrupt handler. */
	if (cur_ops->call) {
		struct rcu_head *rhp = kmalloc(sizeof(*rhp), GFP_NOWAIT);

		if (rhp)
			cur_ops->call(rhp, rcu_torture_timer_cb);
	}
}