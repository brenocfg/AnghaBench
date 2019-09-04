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
struct cgroup_subsys_state {int dummy; } ;
struct dev_cgroup {struct cgroup_subsys_state css; int /*<<< orphan*/  behavior; int /*<<< orphan*/  exceptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCG_DEFAULT_NONE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dev_cgroup* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroup_subsys_state *
devcgroup_css_alloc(struct cgroup_subsys_state *parent_css)
{
	struct dev_cgroup *dev_cgroup;

	dev_cgroup = kzalloc(sizeof(*dev_cgroup), GFP_KERNEL);
	if (!dev_cgroup)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&dev_cgroup->exceptions);
	dev_cgroup->behavior = DEVCG_DEFAULT_NONE;

	return &dev_cgroup->css;
}