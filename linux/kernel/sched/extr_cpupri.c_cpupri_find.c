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
struct task_struct {int /*<<< orphan*/  cpus_ptr; int /*<<< orphan*/  prio; } ;
struct cpupri_vec {int /*<<< orphan*/  mask; int /*<<< orphan*/  count; } ;
struct cpupri {struct cpupri_vec* pri_to_cpu; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CPUPRI_NR_PRIORITIES ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int convert_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_any (struct cpumask*) ; 
 scalar_t__ cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  smp_rmb () ; 

int cpupri_find(struct cpupri *cp, struct task_struct *p,
		struct cpumask *lowest_mask)
{
	int idx = 0;
	int task_pri = convert_prio(p->prio);

	BUG_ON(task_pri >= CPUPRI_NR_PRIORITIES);

	for (idx = 0; idx < task_pri; idx++) {
		struct cpupri_vec *vec  = &cp->pri_to_cpu[idx];
		int skip = 0;

		if (!atomic_read(&(vec)->count))
			skip = 1;
		/*
		 * When looking at the vector, we need to read the counter,
		 * do a memory barrier, then read the mask.
		 *
		 * Note: This is still all racey, but we can deal with it.
		 *  Ideally, we only want to look at masks that are set.
		 *
		 *  If a mask is not set, then the only thing wrong is that we
		 *  did a little more work than necessary.
		 *
		 *  If we read a zero count but the mask is set, because of the
		 *  memory barriers, that can only happen when the highest prio
		 *  task for a run queue has left the run queue, in which case,
		 *  it will be followed by a pull. If the task we are processing
		 *  fails to find a proper place to go, that pull request will
		 *  pull this task if the run queue is running at a lower
		 *  priority.
		 */
		smp_rmb();

		/* Need to do the rmb for every iteration */
		if (skip)
			continue;

		if (cpumask_any_and(p->cpus_ptr, vec->mask) >= nr_cpu_ids)
			continue;

		if (lowest_mask) {
			cpumask_and(lowest_mask, p->cpus_ptr, vec->mask);

			/*
			 * We have to ensure that we have at least one bit
			 * still set in the array, since the map could have
			 * been concurrently emptied between the first and
			 * second reads of vec->mask.  If we hit this
			 * condition, simply act as though we never hit this
			 * priority level and continue on.
			 */
			if (cpumask_any(lowest_mask) >= nr_cpu_ids)
				continue;
		}

		return 1;
	}

	return 0;
}