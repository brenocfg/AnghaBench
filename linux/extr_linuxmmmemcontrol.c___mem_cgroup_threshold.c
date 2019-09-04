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
struct mem_cgroup_threshold_ary {int current_threshold; int size; TYPE_3__* entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  primary; } ;
struct TYPE_4__ {int /*<<< orphan*/  primary; } ;
struct mem_cgroup {TYPE_2__ memsw_thresholds; TYPE_1__ thresholds; } ;
struct TYPE_6__ {unsigned long threshold; int /*<<< orphan*/  eventfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 
 unsigned long mem_cgroup_usage (struct mem_cgroup*,int) ; 
 struct mem_cgroup_threshold_ary* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __mem_cgroup_threshold(struct mem_cgroup *memcg, bool swap)
{
	struct mem_cgroup_threshold_ary *t;
	unsigned long usage;
	int i;

	rcu_read_lock();
	if (!swap)
		t = rcu_dereference(memcg->thresholds.primary);
	else
		t = rcu_dereference(memcg->memsw_thresholds.primary);

	if (!t)
		goto unlock;

	usage = mem_cgroup_usage(memcg, swap);

	/*
	 * current_threshold points to threshold just below or equal to usage.
	 * If it's not true, a threshold was crossed after last
	 * call of __mem_cgroup_threshold().
	 */
	i = t->current_threshold;

	/*
	 * Iterate backward over array of thresholds starting from
	 * current_threshold and check if a threshold is crossed.
	 * If none of thresholds below usage is crossed, we read
	 * only one element of the array here.
	 */
	for (; i >= 0 && unlikely(t->entries[i].threshold > usage); i--)
		eventfd_signal(t->entries[i].eventfd, 1);

	/* i = current_threshold + 1 */
	i++;

	/*
	 * Iterate forward over array of thresholds starting from
	 * current_threshold+1 and check if a threshold is crossed.
	 * If none of thresholds above usage is crossed, we read
	 * only one element of the array here.
	 */
	for (; i < t->size && unlikely(t->entries[i].threshold <= usage); i++)
		eventfd_signal(t->entries[i].eventfd, 1);

	/* Update current_threshold */
	t->current_threshold = i - 1;
unlock:
	rcu_read_unlock();
}