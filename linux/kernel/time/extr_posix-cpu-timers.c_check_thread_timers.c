#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {unsigned long timeout; } ;
struct posix_cputimers {int dummy; } ;
struct task_struct {TYPE_3__* signal; TYPE_1__ rt; struct posix_cputimers posix_cputimers; } ;
struct list_head {int dummy; } ;
struct TYPE_6__ {TYPE_2__* rlim; } ;
struct TYPE_5__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int CPUCLOCK_MAX ; 
 unsigned long HZ ; 
 size_t RLIMIT_RTTIME ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  TICK_DEP_BIT_POSIX_TIMER ; 
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  check_dl_overrun (struct task_struct*) ; 
 scalar_t__ check_rlimit (unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  collect_posix_cputimers (struct posix_cputimers*,int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 scalar_t__ expiry_cache_is_inactive (struct posix_cputimers*) ; 
 unsigned long task_rlimit (struct task_struct*,size_t) ; 
 unsigned long task_rlimit_max (struct task_struct*,size_t) ; 
 int /*<<< orphan*/  task_sample_cputime (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_dep_clear_task (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_thread_timers(struct task_struct *tsk,
				struct list_head *firing)
{
	struct posix_cputimers *pct = &tsk->posix_cputimers;
	u64 samples[CPUCLOCK_MAX];
	unsigned long soft;

	if (dl_task(tsk))
		check_dl_overrun(tsk);

	if (expiry_cache_is_inactive(pct))
		return;

	task_sample_cputime(tsk, samples);
	collect_posix_cputimers(pct, samples, firing);

	/*
	 * Check for the special case thread timers.
	 */
	soft = task_rlimit(tsk, RLIMIT_RTTIME);
	if (soft != RLIM_INFINITY) {
		/* Task RT timeout is accounted in jiffies. RTTIME is usec */
		unsigned long rttime = tsk->rt.timeout * (USEC_PER_SEC / HZ);
		unsigned long hard = task_rlimit_max(tsk, RLIMIT_RTTIME);

		/* At the hard limit, send SIGKILL. No further action. */
		if (hard != RLIM_INFINITY &&
		    check_rlimit(rttime, hard, SIGKILL, true, true))
			return;

		/* At the soft limit, send a SIGXCPU every second */
		if (check_rlimit(rttime, soft, SIGXCPU, true, false)) {
			soft += USEC_PER_SEC;
			tsk->signal->rlim[RLIMIT_RTTIME].rlim_cur = soft;
		}
	}

	if (expiry_cache_is_inactive(pct))
		tick_dep_clear_task(tsk, TICK_DEP_BIT_POSIX_TIMER);
}