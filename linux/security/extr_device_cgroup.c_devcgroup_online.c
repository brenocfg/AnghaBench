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
struct dev_cgroup {int /*<<< orphan*/  behavior; int /*<<< orphan*/  exceptions; } ;
struct cgroup_subsys_state {struct cgroup_subsys_state* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCG_DEFAULT_ALLOW ; 
 struct dev_cgroup* css_to_devcgroup (struct cgroup_subsys_state*) ; 
 int dev_exceptions_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devcgroup_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devcgroup_online(struct cgroup_subsys_state *css)
{
	struct dev_cgroup *dev_cgroup = css_to_devcgroup(css);
	struct dev_cgroup *parent_dev_cgroup = css_to_devcgroup(css->parent);
	int ret = 0;

	mutex_lock(&devcgroup_mutex);

	if (parent_dev_cgroup == NULL)
		dev_cgroup->behavior = DEVCG_DEFAULT_ALLOW;
	else {
		ret = dev_exceptions_copy(&dev_cgroup->exceptions,
					  &parent_dev_cgroup->exceptions);
		if (!ret)
			dev_cgroup->behavior = parent_dev_cgroup->behavior;
	}
	mutex_unlock(&devcgroup_mutex);

	return ret;
}