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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {scalar_t__ dl_overrun; } ;
struct posix_cputimers {int /*<<< orphan*/  expiry_active; int /*<<< orphan*/  timers_active; } ;
struct task_struct {TYPE_2__ dl; struct signal_struct* signal; struct posix_cputimers posix_cputimers; } ;
struct TYPE_3__ {int /*<<< orphan*/  cputime_atomic; } ;
struct signal_struct {TYPE_1__ cputimer; struct posix_cputimers posix_cputimers; } ;

/* Variables and functions */
 int CPUCLOCK_MAX ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 int /*<<< orphan*/  expiry_cache_is_inactive (struct posix_cputimers*) ; 
 int /*<<< orphan*/  proc_sample_cputime_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ task_cputimers_expired (int /*<<< orphan*/ *,struct posix_cputimers*) ; 
 int /*<<< orphan*/  task_sample_cputime (struct task_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool fastpath_timer_check(struct task_struct *tsk)
{
	struct posix_cputimers *pct = &tsk->posix_cputimers;
	struct signal_struct *sig;

	if (!expiry_cache_is_inactive(pct)) {
		u64 samples[CPUCLOCK_MAX];

		task_sample_cputime(tsk, samples);
		if (task_cputimers_expired(samples, pct))
			return true;
	}

	sig = tsk->signal;
	pct = &sig->posix_cputimers;
	/*
	 * Check if thread group timers expired when timers are active and
	 * no other thread in the group is already handling expiry for
	 * thread group cputimers. These fields are read without the
	 * sighand lock. However, this is fine because this is meant to be
	 * a fastpath heuristic to determine whether we should try to
	 * acquire the sighand lock to handle timer expiry.
	 *
	 * In the worst case scenario, if concurrently timers_active is set
	 * or expiry_active is cleared, but the current thread doesn't see
	 * the change yet, the timer checks are delayed until the next
	 * thread in the group gets a scheduler interrupt to handle the
	 * timer. This isn't an issue in practice because these types of
	 * delays with signals actually getting sent are expected.
	 */
	if (READ_ONCE(pct->timers_active) && !READ_ONCE(pct->expiry_active)) {
		u64 samples[CPUCLOCK_MAX];

		proc_sample_cputime_atomic(&sig->cputimer.cputime_atomic,
					   samples);

		if (task_cputimers_expired(samples, pct))
			return true;
	}

	if (dl_task(tsk) && tsk->dl.dl_overrun)
		return true;

	return false;
}