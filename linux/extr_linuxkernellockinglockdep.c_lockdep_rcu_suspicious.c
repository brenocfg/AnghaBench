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
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  debug_locks ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  lockdep_print_held_locks (struct task_struct*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  print_kernel_ident () ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 int /*<<< orphan*/  rcu_lockdep_current_cpu_online () ; 
 int /*<<< orphan*/  rcu_scheduler_active ; 

void lockdep_rcu_suspicious(const char *file, const int line, const char *s)
{
	struct task_struct *curr = current;

	/* Note: the following can be executed concurrently, so be careful. */
	pr_warn("\n");
	pr_warn("=============================\n");
	pr_warn("WARNING: suspicious RCU usage\n");
	print_kernel_ident();
	pr_warn("-----------------------------\n");
	pr_warn("%s:%d %s!\n", file, line, s);
	pr_warn("\nother info that might help us debug this:\n\n");
	pr_warn("\n%srcu_scheduler_active = %d, debug_locks = %d\n",
	       !rcu_lockdep_current_cpu_online()
			? "RCU used illegally from offline CPU!\n"
			: !rcu_is_watching()
				? "RCU used illegally from idle CPU!\n"
				: "",
	       rcu_scheduler_active, debug_locks);

	/*
	 * If a CPU is in the RCU-free window in idle (ie: in the section
	 * between rcu_idle_enter() and rcu_idle_exit(), then RCU
	 * considers that CPU to be in an "extended quiescent state",
	 * which means that RCU will be completely ignoring that CPU.
	 * Therefore, rcu_read_lock() and friends have absolutely no
	 * effect on a CPU running in that state. In other words, even if
	 * such an RCU-idle CPU has called rcu_read_lock(), RCU might well
	 * delete data structures out from under it.  RCU really has no
	 * choice here: we need to keep an RCU-free window in idle where
	 * the CPU may possibly enter into low power mode. This way we can
	 * notice an extended quiescent state to other CPUs that started a grace
	 * period. Otherwise we would delay any grace period as long as we run
	 * in the idle task.
	 *
	 * So complain bitterly if someone does call rcu_read_lock(),
	 * rcu_read_lock_bh() and so on from extended quiescent states.
	 */
	if (!rcu_is_watching())
		pr_warn("RCU used illegally from extended quiescent state!\n");

	lockdep_print_held_locks(curr);
	pr_warn("\nstack backtrace:\n");
	dump_stack();
}