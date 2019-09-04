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
struct timespec64 {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int cpu_clock_sample (int /*<<< orphan*/  const,struct task_struct*,int /*<<< orphan*/ *) ; 
 int cpu_clock_sample_group (int /*<<< orphan*/  const,struct task_struct*,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 
 scalar_t__ same_thread_group (struct task_struct*,struct task_struct*) ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 

__attribute__((used)) static int posix_cpu_clock_get_task(struct task_struct *tsk,
				    const clockid_t which_clock,
				    struct timespec64 *tp)
{
	int err = -EINVAL;
	u64 rtn;

	if (CPUCLOCK_PERTHREAD(which_clock)) {
		if (same_thread_group(tsk, current))
			err = cpu_clock_sample(which_clock, tsk, &rtn);
	} else {
		if (tsk == current || thread_group_leader(tsk))
			err = cpu_clock_sample_group(which_clock, tsk, &rtn);
	}

	if (!err)
		*tp = ns_to_timespec64(rtn);

	return err;
}