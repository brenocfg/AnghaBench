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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
#define  CPUCLOCK_PROF 130 
#define  CPUCLOCK_SCHED 129 
#define  CPUCLOCK_VIRT 128 
 int CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  prof_ticks (struct task_struct*) ; 
 int /*<<< orphan*/  task_sched_runtime (struct task_struct*) ; 
 int /*<<< orphan*/  virt_ticks (struct task_struct*) ; 

__attribute__((used)) static int cpu_clock_sample(const clockid_t which_clock,
			    struct task_struct *p, u64 *sample)
{
	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		*sample = prof_ticks(p);
		break;
	case CPUCLOCK_VIRT:
		*sample = virt_ticks(p);
		break;
	case CPUCLOCK_SCHED:
		*sample = task_sched_runtime(p);
		break;
	}
	return 0;
}