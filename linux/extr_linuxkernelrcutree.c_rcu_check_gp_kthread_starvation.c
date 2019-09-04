#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rcu_state {TYPE_1__* gp_kthread; int /*<<< orphan*/  gp_state; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  name; int /*<<< orphan*/  gp_activity; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp_state_getname (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ rcu_seq_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_show_task (TYPE_1__*) ; 
 int task_cpu (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_process (TYPE_1__*) ; 

__attribute__((used)) static void rcu_check_gp_kthread_starvation(struct rcu_state *rsp)
{
	unsigned long gpa;
	unsigned long j;

	j = jiffies;
	gpa = READ_ONCE(rsp->gp_activity);
	if (j - gpa > 2 * HZ) {
		pr_err("%s kthread starved for %ld jiffies! g%ld f%#x %s(%d) ->state=%#lx ->cpu=%d\n",
		       rsp->name, j - gpa,
		       (long)rcu_seq_current(&rsp->gp_seq),
		       rsp->gp_flags,
		       gp_state_getname(rsp->gp_state), rsp->gp_state,
		       rsp->gp_kthread ? rsp->gp_kthread->state : ~0,
		       rsp->gp_kthread ? task_cpu(rsp->gp_kthread) : -1);
		if (rsp->gp_kthread) {
			pr_err("RCU grace-period kthread stack dump:\n");
			sched_show_task(rsp->gp_kthread);
			wake_up_process(rsp->gp_kthread);
		}
	}
}