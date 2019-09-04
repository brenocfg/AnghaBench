#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct task_struct {TYPE_2__* signal; } ;
struct TYPE_3__ {scalar_t__ virt_exp; scalar_t__ prof_exp; } ;
struct TYPE_4__ {TYPE_1__ cputime_expires; } ;

/* Variables and functions */
#define  CPUCLOCK_PROF 129 
 unsigned int CPUCLOCK_SCHED ; 
#define  CPUCLOCK_VIRT 128 
 int EINVAL ; 
 int /*<<< orphan*/  TICK_DEP_BIT_POSIX_TIMER ; 
 scalar_t__ TICK_NSEC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int cpu_timer_sample_group (unsigned int,struct task_struct*,scalar_t__*) ; 
 int /*<<< orphan*/  expires_gt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tick_dep_set_signal (TYPE_2__*,int /*<<< orphan*/ ) ; 

void set_process_cpu_timer(struct task_struct *tsk, unsigned int clock_idx,
			   u64 *newval, u64 *oldval)
{
	u64 now;
	int ret;

	WARN_ON_ONCE(clock_idx == CPUCLOCK_SCHED);
	ret = cpu_timer_sample_group(clock_idx, tsk, &now);

	if (oldval && ret != -EINVAL) {
		/*
		 * We are setting itimer. The *oldval is absolute and we update
		 * it to be relative, *newval argument is relative and we update
		 * it to be absolute.
		 */
		if (*oldval) {
			if (*oldval <= now) {
				/* Just about to fire. */
				*oldval = TICK_NSEC;
			} else {
				*oldval -= now;
			}
		}

		if (!*newval)
			return;
		*newval += now;
	}

	/*
	 * Update expiration cache if we are the earliest timer, or eventually
	 * RLIMIT_CPU limit is earlier than prof_exp cpu timer expire.
	 */
	switch (clock_idx) {
	case CPUCLOCK_PROF:
		if (expires_gt(tsk->signal->cputime_expires.prof_exp, *newval))
			tsk->signal->cputime_expires.prof_exp = *newval;
		break;
	case CPUCLOCK_VIRT:
		if (expires_gt(tsk->signal->cputime_expires.virt_exp, *newval))
			tsk->signal->cputime_expires.virt_exp = *newval;
		break;
	}

	tick_dep_set_signal(tsk->signal, TICK_DEP_BIT_POSIX_TIMER);
}