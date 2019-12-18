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
struct cpuset {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int private; } ;
typedef  int cpuset_filetype_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_CPU_EXCLUSIVE ; 
 int /*<<< orphan*/  CS_MEMORY_MIGRATE ; 
 int /*<<< orphan*/  CS_MEM_EXCLUSIVE ; 
 int /*<<< orphan*/  CS_MEM_HARDWALL ; 
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 int /*<<< orphan*/  CS_SPREAD_PAGE ; 
 int /*<<< orphan*/  CS_SPREAD_SLAB ; 
 int EINVAL ; 
 int ENODEV ; 
#define  FILE_CPU_EXCLUSIVE 135 
#define  FILE_MEMORY_MIGRATE 134 
#define  FILE_MEMORY_PRESSURE_ENABLED 133 
#define  FILE_MEM_EXCLUSIVE 132 
#define  FILE_MEM_HARDWALL 131 
#define  FILE_SCHED_LOAD_BALANCE 130 
#define  FILE_SPREAD_PAGE 129 
#define  FILE_SPREAD_SLAB 128 
 int cpuset_memory_pressure_enabled ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  is_cpuset_online (struct cpuset*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int update_flag (int /*<<< orphan*/ ,struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuset_write_u64(struct cgroup_subsys_state *css, struct cftype *cft,
			    u64 val)
{
	struct cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->private;
	int retval = 0;

	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);
	if (!is_cpuset_online(cs)) {
		retval = -ENODEV;
		goto out_unlock;
	}

	switch (type) {
	case FILE_CPU_EXCLUSIVE:
		retval = update_flag(CS_CPU_EXCLUSIVE, cs, val);
		break;
	case FILE_MEM_EXCLUSIVE:
		retval = update_flag(CS_MEM_EXCLUSIVE, cs, val);
		break;
	case FILE_MEM_HARDWALL:
		retval = update_flag(CS_MEM_HARDWALL, cs, val);
		break;
	case FILE_SCHED_LOAD_BALANCE:
		retval = update_flag(CS_SCHED_LOAD_BALANCE, cs, val);
		break;
	case FILE_MEMORY_MIGRATE:
		retval = update_flag(CS_MEMORY_MIGRATE, cs, val);
		break;
	case FILE_MEMORY_PRESSURE_ENABLED:
		cpuset_memory_pressure_enabled = !!val;
		break;
	case FILE_SPREAD_PAGE:
		retval = update_flag(CS_SPREAD_PAGE, cs, val);
		break;
	case FILE_SPREAD_SLAB:
		retval = update_flag(CS_SPREAD_SLAB, cs, val);
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