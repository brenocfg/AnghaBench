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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct task_cputime {scalar_t__ sum_exec_runtime; scalar_t__ utime; scalar_t__ stime; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
#define  CPUCLOCK_PROF 130 
#define  CPUCLOCK_SCHED 129 
#define  CPUCLOCK_VIRT 128 
 int CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  thread_group_cputime (struct task_struct*,struct task_cputime*) ; 

__attribute__((used)) static int cpu_clock_sample_group(const clockid_t which_clock,
				  struct task_struct *p,
				  u64 *sample)
{
	struct task_cputime cputime;

	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		thread_group_cputime(p, &cputime);
		*sample = cputime.utime + cputime.stime;
		break;
	case CPUCLOCK_VIRT:
		thread_group_cputime(p, &cputime);
		*sample = cputime.utime;
		break;
	case CPUCLOCK_SCHED:
		thread_group_cputime(p, &cputime);
		*sample = cputime.sum_exec_runtime;
		break;
	}
	return 0;
}