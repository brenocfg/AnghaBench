#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_5__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_EVENT_EXEC ; 
 int /*<<< orphan*/  audit_bprm (struct linux_binprm*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  proc_exec_connector (TYPE_1__*) ; 
 int /*<<< orphan*/  ptrace_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int search_binary_handler (struct linux_binprm*) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr_ns (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sched_process_exec (TYPE_1__*,int /*<<< orphan*/ ,struct linux_binprm*) ; 

__attribute__((used)) static int exec_binprm(struct linux_binprm *bprm)
{
	pid_t old_pid, old_vpid;
	int ret;

	/* Need to fetch pid before load_binary changes it */
	old_pid = current->pid;
	rcu_read_lock();
	old_vpid = task_pid_nr_ns(current, task_active_pid_ns(current->parent));
	rcu_read_unlock();

	ret = search_binary_handler(bprm);
	if (ret >= 0) {
		audit_bprm(bprm);
		trace_sched_process_exec(current, old_pid, bprm);
		ptrace_event(PTRACE_EVENT_EXEC, old_vpid);
		proc_exec_connector(current);
	}

	return ret;
}