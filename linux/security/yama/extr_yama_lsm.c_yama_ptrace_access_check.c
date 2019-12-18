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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 int EPERM ; 
 unsigned int PTRACE_MODE_ATTACH ; 
 unsigned int PTRACE_MODE_NOAUDIT ; 
#define  YAMA_SCOPE_CAPABILITY 131 
#define  YAMA_SCOPE_DISABLED 130 
#define  YAMA_SCOPE_NO_ATTACH 129 
#define  YAMA_SCOPE_RELATIONAL 128 
 TYPE_1__* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_alive (struct task_struct*) ; 
 int ptrace_scope ; 
 int /*<<< orphan*/  ptracer_exception_found (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  report_access (char*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_is_descendant (int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static int yama_ptrace_access_check(struct task_struct *child,
				    unsigned int mode)
{
	int rc = 0;

	/* require ptrace target be a child of ptracer on attach */
	if (mode & PTRACE_MODE_ATTACH) {
		switch (ptrace_scope) {
		case YAMA_SCOPE_DISABLED:
			/* No additional restrictions. */
			break;
		case YAMA_SCOPE_RELATIONAL:
			rcu_read_lock();
			if (!pid_alive(child))
				rc = -EPERM;
			if (!rc && !task_is_descendant(current, child) &&
			    !ptracer_exception_found(current, child) &&
			    !ns_capable(__task_cred(child)->user_ns, CAP_SYS_PTRACE))
				rc = -EPERM;
			rcu_read_unlock();
			break;
		case YAMA_SCOPE_CAPABILITY:
			rcu_read_lock();
			if (!ns_capable(__task_cred(child)->user_ns, CAP_SYS_PTRACE))
				rc = -EPERM;
			rcu_read_unlock();
			break;
		case YAMA_SCOPE_NO_ATTACH:
		default:
			rc = -EPERM;
			break;
		}
	}

	if (rc && (mode & PTRACE_MODE_NOAUDIT) == 0)
		report_access("attach", child, current);

	return rc;
}