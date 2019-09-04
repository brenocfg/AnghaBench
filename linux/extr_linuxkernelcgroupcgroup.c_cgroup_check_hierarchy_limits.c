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
struct cgroup {scalar_t__ nr_descendants; scalar_t__ max_descendants; int max_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_mutex ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cgroup_check_hierarchy_limits(struct cgroup *parent)
{
	struct cgroup *cgroup;
	int ret = false;
	int level = 1;

	lockdep_assert_held(&cgroup_mutex);

	for (cgroup = parent; cgroup; cgroup = cgroup_parent(cgroup)) {
		if (cgroup->nr_descendants >= cgroup->max_descendants)
			goto fail;

		if (level > cgroup->max_depth)
			goto fail;

		level++;
	}

	ret = true;
fail:
	return ret;
}