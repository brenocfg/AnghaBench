#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mem_cgroup_thresholds {TYPE_2__* primary; TYPE_2__* spare; } ;
struct mem_cgroup_threshold_ary {int size; int current_threshold; TYPE_1__* entries; } ;
struct mem_cgroup_threshold {int dummy; } ;
struct mem_cgroup {int /*<<< orphan*/  thresholds_lock; struct mem_cgroup_thresholds memsw_thresholds; struct mem_cgroup_thresholds thresholds; } ;
struct eventfd_ctx {int dummy; } ;
typedef  enum res_type { ____Placeholder_res_type } res_type ;
struct TYPE_6__ {int size; int /*<<< orphan*/  entries; } ;
struct TYPE_5__ {unsigned long threshold; struct eventfd_ctx* eventfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _MEM ; 
 int _MEMSWAP ; 
 int /*<<< orphan*/  __mem_cgroup_threshold (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  compare_thresholds ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 struct mem_cgroup_threshold_ary* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long mem_cgroup_usage (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int page_counter_memparse (char const*,char*,unsigned long*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (TYPE_2__*,struct mem_cgroup_threshold_ary*) ; 
 int /*<<< orphan*/  sort (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct mem_cgroup_threshold_ary*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int __mem_cgroup_usage_register_event(struct mem_cgroup *memcg,
	struct eventfd_ctx *eventfd, const char *args, enum res_type type)
{
	struct mem_cgroup_thresholds *thresholds;
	struct mem_cgroup_threshold_ary *new;
	unsigned long threshold;
	unsigned long usage;
	int i, size, ret;

	ret = page_counter_memparse(args, "-1", &threshold);
	if (ret)
		return ret;

	mutex_lock(&memcg->thresholds_lock);

	if (type == _MEM) {
		thresholds = &memcg->thresholds;
		usage = mem_cgroup_usage(memcg, false);
	} else if (type == _MEMSWAP) {
		thresholds = &memcg->memsw_thresholds;
		usage = mem_cgroup_usage(memcg, true);
	} else
		BUG();

	/* Check if a threshold crossed before adding a new one */
	if (thresholds->primary)
		__mem_cgroup_threshold(memcg, type == _MEMSWAP);

	size = thresholds->primary ? thresholds->primary->size + 1 : 1;

	/* Allocate memory for new array of thresholds */
	new = kmalloc(struct_size(new, entries, size), GFP_KERNEL);
	if (!new) {
		ret = -ENOMEM;
		goto unlock;
	}
	new->size = size;

	/* Copy thresholds (if any) to new array */
	if (thresholds->primary) {
		memcpy(new->entries, thresholds->primary->entries, (size - 1) *
				sizeof(struct mem_cgroup_threshold));
	}

	/* Add new threshold */
	new->entries[size - 1].eventfd = eventfd;
	new->entries[size - 1].threshold = threshold;

	/* Sort thresholds. Registering of new threshold isn't time-critical */
	sort(new->entries, size, sizeof(struct mem_cgroup_threshold),
			compare_thresholds, NULL);

	/* Find current threshold */
	new->current_threshold = -1;
	for (i = 0; i < size; i++) {
		if (new->entries[i].threshold <= usage) {
			/*
			 * new->current_threshold will not be used until
			 * rcu_assign_pointer(), so it's safe to increment
			 * it here.
			 */
			++new->current_threshold;
		} else
			break;
	}

	/* Free old spare buffer and save old primary buffer as spare */
	kfree(thresholds->spare);
	thresholds->spare = thresholds->primary;

	rcu_assign_pointer(thresholds->primary, new);

	/* To be sure that nobody uses thresholds */
	synchronize_rcu();

unlock:
	mutex_unlock(&memcg->thresholds_lock);

	return ret;
}