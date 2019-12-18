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
struct cpuset {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int private; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int cpuset_filetype_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  FILE_SCHED_RELAX_DOMAIN_LEVEL 128 
 int /*<<< orphan*/  cpuset_rwsem ; 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  is_cpuset_online (struct cpuset*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int update_relax_domain_level (struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuset_write_s64(struct cgroup_subsys_state *css, struct cftype *cft,
			    s64 val)
{
	struct cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->private;
	int retval = -ENODEV;

	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);
	if (!is_cpuset_online(cs))
		goto out_unlock;

	switch (type) {
	case FILE_SCHED_RELAX_DOMAIN_LEVEL:
		retval = update_relax_domain_level(cs, val);
		break;
	default:
		retval = -EINVAL;
		break;
	}
out_unlock:
	percpu_up_write(&cpuset_rwsem);
	put_online_cpus();
	return retval;
}