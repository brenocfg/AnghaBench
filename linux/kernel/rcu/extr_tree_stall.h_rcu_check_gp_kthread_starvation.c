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
struct task_struct {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  gp_state; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  name; int /*<<< orphan*/  gp_activity; struct task_struct* gp_kthread; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp_state_getname (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ rcu_seq_current (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  sched_show_task (struct task_struct*) ; 
 int task_cpu (struct task_struct*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void rcu_check_gp_kthread_starvation(void)
{
	struct task_struct *gpk = rcu_state.gp_kthread;
	unsigned long j;

	j = jiffies - READ_ONCE(rcu_state.gp_activity);
	if (j > 2 * HZ) {
		pr_err("%s kthread starved for %ld jiffies! g%ld f%#x %s(%d) ->state=%#lx ->cpu=%d\n",
		       rcu_state.name, j,
		       (long)rcu_seq_current(&rcu_state.gp_seq),
		       READ_ONCE(rcu_state.gp_flags),
		       gp_state_getname(rcu_state.gp_state), rcu_state.gp_state,
		       gpk ? gpk->state : ~0, gpk ? task_cpu(gpk) : -1);
		if (gpk) {
			pr_err("RCU grace-period kthread stack dump:\n");
			sched_show_task(gpk);
			wake_up_process(gpk);
		}
	}
}