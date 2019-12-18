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
struct TYPE_2__ {scalar_t__ s; } ;
struct task_struct {int rcu_tasks_holdout; int rcu_tasks_idle_cpu; int /*<<< orphan*/  rcu_tasks_holdout_list; int /*<<< orphan*/  rcu_node_entry; int /*<<< orphan*/ * rcu_blocked_node; TYPE_1__ rcu_read_unlock_special; scalar_t__ rcu_read_lock_nesting; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rcu_copy_process(struct task_struct *p)
{
#ifdef CONFIG_PREEMPT_RCU
	p->rcu_read_lock_nesting = 0;
	p->rcu_read_unlock_special.s = 0;
	p->rcu_blocked_node = NULL;
	INIT_LIST_HEAD(&p->rcu_node_entry);
#endif /* #ifdef CONFIG_PREEMPT_RCU */
#ifdef CONFIG_TASKS_RCU
	p->rcu_tasks_holdout = false;
	INIT_LIST_HEAD(&p->rcu_tasks_holdout_list);
	p->rcu_tasks_idle_cpu = -1;
#endif /* #ifdef CONFIG_TASKS_RCU */
}