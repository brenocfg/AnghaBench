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
struct task_struct {int /*<<< orphan*/  group_leader; TYPE_1__* signal; int /*<<< orphan*/  sighand; } ;
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
struct TYPE_2__ {struct rlimit* rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  CONFIG_POSIX_TIMERS ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int RLIMIT_CPU ; 
 unsigned int RLIMIT_NOFILE ; 
 scalar_t__ RLIM_INFINITY ; 
 unsigned int RLIM_NLIMITS ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int security_task_setrlimit (struct task_struct*,unsigned int,struct rlimit*) ; 
 scalar_t__ sysctl_nr_open ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  update_rlimit_cpu (struct task_struct*,scalar_t__) ; 

int do_prlimit(struct task_struct *tsk, unsigned int resource,
		struct rlimit *new_rlim, struct rlimit *old_rlim)
{
	struct rlimit *rlim;
	int retval = 0;

	if (resource >= RLIM_NLIMITS)
		return -EINVAL;
	if (new_rlim) {
		if (new_rlim->rlim_cur > new_rlim->rlim_max)
			return -EINVAL;
		if (resource == RLIMIT_NOFILE &&
				new_rlim->rlim_max > sysctl_nr_open)
			return -EPERM;
	}

	/* protect tsk->signal and tsk->sighand from disappearing */
	read_lock(&tasklist_lock);
	if (!tsk->sighand) {
		retval = -ESRCH;
		goto out;
	}

	rlim = tsk->signal->rlim + resource;
	task_lock(tsk->group_leader);
	if (new_rlim) {
		/* Keep the capable check against init_user_ns until
		   cgroups can contain all limits */
		if (new_rlim->rlim_max > rlim->rlim_max &&
				!capable(CAP_SYS_RESOURCE))
			retval = -EPERM;
		if (!retval)
			retval = security_task_setrlimit(tsk, resource, new_rlim);
	}
	if (!retval) {
		if (old_rlim)
			*old_rlim = *rlim;
		if (new_rlim)
			*rlim = *new_rlim;
	}
	task_unlock(tsk->group_leader);

	/*
	 * RLIMIT_CPU handling. Arm the posix CPU timer if the limit is not
	 * infite. In case of RLIM_INFINITY the posix CPU timer code
	 * ignores the rlimit.
	 */
	 if (!retval && new_rlim && resource == RLIMIT_CPU &&
	     new_rlim->rlim_cur != RLIM_INFINITY &&
	     IS_ENABLED(CONFIG_POSIX_TIMERS))
		update_rlimit_cpu(tsk, new_rlim->rlim_cur);
out:
	read_unlock(&tasklist_lock);
	return retval;
}