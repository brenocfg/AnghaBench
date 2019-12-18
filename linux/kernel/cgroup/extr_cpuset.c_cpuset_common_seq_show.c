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
struct seq_file {int dummy; } ;
struct cpuset {int /*<<< orphan*/  subparts_cpus; int /*<<< orphan*/  effective_mems; int /*<<< orphan*/  effective_cpus; int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_allowed; } ;
typedef  int cpuset_filetype_t ;
struct TYPE_2__ {int private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FILE_CPULIST 132 
#define  FILE_EFFECTIVE_CPULIST 131 
#define  FILE_EFFECTIVE_MEMLIST 130 
#define  FILE_MEMLIST 129 
#define  FILE_SUBPARTS_CPULIST 128 
 int /*<<< orphan*/  callback_lock ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ ) ; 
 struct cpuset* css_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodemask_pr_args (int /*<<< orphan*/ *) ; 
 TYPE_1__* seq_cft (struct seq_file*) ; 
 int /*<<< orphan*/  seq_css (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpuset_common_seq_show(struct seq_file *sf, void *v)
{
	struct cpuset *cs = css_cs(seq_css(sf));
	cpuset_filetype_t type = seq_cft(sf)->private;
	int ret = 0;

	spin_lock_irq(&callback_lock);

	switch (type) {
	case FILE_CPULIST:
		seq_printf(sf, "%*pbl\n", cpumask_pr_args(cs->cpus_allowed));
		break;
	case FILE_MEMLIST:
		seq_printf(sf, "%*pbl\n", nodemask_pr_args(&cs->mems_allowed));
		break;
	case FILE_EFFECTIVE_CPULIST:
		seq_printf(sf, "%*pbl\n", cpumask_pr_args(cs->effective_cpus));
		break;
	case FILE_EFFECTIVE_MEMLIST:
		seq_printf(sf, "%*pbl\n", nodemask_pr_args(&cs->effective_mems));
		break;
	case FILE_SUBPARTS_CPULIST:
		seq_printf(sf, "%*pbl\n", cpumask_pr_args(cs->subparts_cpus));
		break;
	default:
		ret = -EINVAL;
	}

	spin_unlock_irq(&callback_lock);
	return ret;
}