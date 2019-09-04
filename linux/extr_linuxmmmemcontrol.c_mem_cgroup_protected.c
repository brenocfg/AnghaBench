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
struct TYPE_2__ {unsigned long min; unsigned long low; unsigned long emin; unsigned long elow; int /*<<< orphan*/  children_low_usage; int /*<<< orphan*/  children_min_usage; } ;
struct mem_cgroup {TYPE_1__ memory; } ;
typedef  enum mem_cgroup_protection { ____Placeholder_mem_cgroup_protection } mem_cgroup_protection ;

/* Variables and functions */
 int MEMCG_PROT_LOW ; 
 int MEMCG_PROT_MIN ; 
 int MEMCG_PROT_NONE ; 
 unsigned long READ_ONCE (unsigned long) ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 unsigned long min (unsigned long,unsigned long) ; 
 unsigned long page_counter_read (TYPE_1__*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 struct mem_cgroup* root_mem_cgroup ; 

enum mem_cgroup_protection mem_cgroup_protected(struct mem_cgroup *root,
						struct mem_cgroup *memcg)
{
	struct mem_cgroup *parent;
	unsigned long emin, parent_emin;
	unsigned long elow, parent_elow;
	unsigned long usage;

	if (mem_cgroup_disabled())
		return MEMCG_PROT_NONE;

	if (!root)
		root = root_mem_cgroup;
	if (memcg == root)
		return MEMCG_PROT_NONE;

	usage = page_counter_read(&memcg->memory);
	if (!usage)
		return MEMCG_PROT_NONE;

	emin = memcg->memory.min;
	elow = memcg->memory.low;

	parent = parent_mem_cgroup(memcg);
	/* No parent means a non-hierarchical mode on v1 memcg */
	if (!parent)
		return MEMCG_PROT_NONE;

	if (parent == root)
		goto exit;

	parent_emin = READ_ONCE(parent->memory.emin);
	emin = min(emin, parent_emin);
	if (emin && parent_emin) {
		unsigned long min_usage, siblings_min_usage;

		min_usage = min(usage, memcg->memory.min);
		siblings_min_usage = atomic_long_read(
			&parent->memory.children_min_usage);

		if (min_usage && siblings_min_usage)
			emin = min(emin, parent_emin * min_usage /
				   siblings_min_usage);
	}

	parent_elow = READ_ONCE(parent->memory.elow);
	elow = min(elow, parent_elow);
	if (elow && parent_elow) {
		unsigned long low_usage, siblings_low_usage;

		low_usage = min(usage, memcg->memory.low);
		siblings_low_usage = atomic_long_read(
			&parent->memory.children_low_usage);

		if (low_usage && siblings_low_usage)
			elow = min(elow, parent_elow * low_usage /
				   siblings_low_usage);
	}

exit:
	memcg->memory.emin = emin;
	memcg->memory.elow = elow;

	if (usage <= emin)
		return MEMCG_PROT_MIN;
	else if (usage <= elow)
		return MEMCG_PROT_LOW;
	else
		return MEMCG_PROT_NONE;
}