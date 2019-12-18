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
typedef  int /*<<< orphan*/  u64 ;
struct thread_group_cputimer {int /*<<< orphan*/  cputime_atomic; } ;
struct task_struct {TYPE_1__* signal; } ;
struct posix_cputimers {int /*<<< orphan*/  timers_active; } ;
typedef  size_t clockid_t ;
struct TYPE_2__ {struct posix_cputimers posix_cputimers; struct thread_group_cputimer cputimer; } ;

/* Variables and functions */
 int CPUCLOCK_MAX ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __thread_group_cputime (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_sample_cputime_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_start_cputime (struct task_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 cpu_clock_sample_group(const clockid_t clkid, struct task_struct *p,
				  bool start)
{
	struct thread_group_cputimer *cputimer = &p->signal->cputimer;
	struct posix_cputimers *pct = &p->signal->posix_cputimers;
	u64 samples[CPUCLOCK_MAX];

	if (!READ_ONCE(pct->timers_active)) {
		if (start)
			thread_group_start_cputime(p, samples);
		else
			__thread_group_cputime(p, samples);
	} else {
		proc_sample_cputime_atomic(&cputimer->cputime_atomic, samples);
	}

	return samples[clkid];
}