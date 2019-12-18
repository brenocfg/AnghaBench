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
struct cftype {int /*<<< orphan*/  node; int /*<<< orphan*/  ss; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  cgroup_apply_cftypes (struct cftype*,int) ; 
 int /*<<< orphan*/  cgroup_exit_cftypes (struct cftype*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cgroup_rm_cftypes_locked(struct cftype *cfts)
{
	lockdep_assert_held(&cgroup_mutex);

	if (!cfts || !cfts[0].ss)
		return -ENOENT;

	list_del(&cfts->node);
	cgroup_apply_cftypes(cfts, false);
	cgroup_exit_cftypes(cfts);
	return 0;
}