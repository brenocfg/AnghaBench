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
typedef  scalar_t__ u64 ;
struct task_struct {struct signal_struct* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  cputime_atomic; } ;
struct posix_cputimers {int expiry_active; TYPE_3__* bases; int /*<<< orphan*/  timers_active; } ;
struct signal_struct {TYPE_2__* rlim; int /*<<< orphan*/ * it; TYPE_1__ cputimer; struct posix_cputimers posix_cputimers; } ;
struct list_head {int dummy; } ;
struct TYPE_6__ {scalar_t__ nextevt; } ;
struct TYPE_5__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int CPUCLOCK_MAX ; 
 size_t CPUCLOCK_PROF ; 
 size_t CPUCLOCK_VIRT ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t RLIMIT_CPU ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGPROF ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  check_cpu_itimer (struct task_struct*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ check_rlimit (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  collect_posix_cputimers (struct posix_cputimers*,scalar_t__*,struct list_head*) ; 
 scalar_t__ expiry_cache_is_inactive (struct posix_cputimers*) ; 
 int /*<<< orphan*/  proc_sample_cputime_atomic (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  stop_process_timers (struct signal_struct* const) ; 
 unsigned long task_rlimit (struct task_struct*,size_t) ; 
 unsigned long task_rlimit_max (struct task_struct*,size_t) ; 

__attribute__((used)) static void check_process_timers(struct task_struct *tsk,
				 struct list_head *firing)
{
	struct signal_struct *const sig = tsk->signal;
	struct posix_cputimers *pct = &sig->posix_cputimers;
	u64 samples[CPUCLOCK_MAX];
	unsigned long soft;

	/*
	 * If there are no active process wide timers (POSIX 1.b, itimers,
	 * RLIMIT_CPU) nothing to check. Also skip the process wide timer
	 * processing when there is already another task handling them.
	 */
	if (!READ_ONCE(pct->timers_active) || pct->expiry_active)
		return;

	/*
	 * Signify that a thread is checking for process timers.
	 * Write access to this field is protected by the sighand lock.
	 */
	pct->expiry_active = true;

	/*
	 * Collect the current process totals. Group accounting is active
	 * so the sample can be taken directly.
	 */
	proc_sample_cputime_atomic(&sig->cputimer.cputime_atomic, samples);
	collect_posix_cputimers(pct, samples, firing);

	/*
	 * Check for the special case process timers.
	 */
	check_cpu_itimer(tsk, &sig->it[CPUCLOCK_PROF],
			 &pct->bases[CPUCLOCK_PROF].nextevt,
			 samples[CPUCLOCK_PROF], SIGPROF);
	check_cpu_itimer(tsk, &sig->it[CPUCLOCK_VIRT],
			 &pct->bases[CPUCLOCK_VIRT].nextevt,
			 samples[CPUCLOCK_VIRT], SIGVTALRM);

	soft = task_rlimit(tsk, RLIMIT_CPU);
	if (soft != RLIM_INFINITY) {
		/* RLIMIT_CPU is in seconds. Samples are nanoseconds */
		unsigned long hard = task_rlimit_max(tsk, RLIMIT_CPU);
		u64 ptime = samples[CPUCLOCK_PROF];
		u64 softns = (u64)soft * NSEC_PER_SEC;
		u64 hardns = (u64)hard * NSEC_PER_SEC;

		/* At the hard limit, send SIGKILL. No further action. */
		if (hard != RLIM_INFINITY &&
		    check_rlimit(ptime, hardns, SIGKILL, false, true))
			return;

		/* At the soft limit, send a SIGXCPU every second */
		if (check_rlimit(ptime, softns, SIGXCPU, false, false)) {
			sig->rlim[RLIMIT_CPU].rlim_cur = soft + 1;
			softns += NSEC_PER_SEC;
		}

		/* Update the expiry cache */
		if (softns < pct->bases[CPUCLOCK_PROF].nextevt)
			pct->bases[CPUCLOCK_PROF].nextevt = softns;
	}

	if (expiry_cache_is_inactive(pct))
		stop_process_timers(sig);

	pct->expiry_active = false;
}