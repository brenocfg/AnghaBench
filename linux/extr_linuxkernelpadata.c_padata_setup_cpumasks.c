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
struct TYPE_2__ {int /*<<< orphan*/  cbcpu; int /*<<< orphan*/  pcpu; } ;
struct parallel_data {TYPE_1__ cpumask; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int padata_setup_cpumasks(struct parallel_data *pd,
				 const struct cpumask *pcpumask,
				 const struct cpumask *cbcpumask)
{
	if (!alloc_cpumask_var(&pd->cpumask.pcpu, GFP_KERNEL))
		return -ENOMEM;

	cpumask_and(pd->cpumask.pcpu, pcpumask, cpu_online_mask);
	if (!alloc_cpumask_var(&pd->cpumask.cbcpu, GFP_KERNEL)) {
		free_cpumask_var(pd->cpumask.pcpu);
		return -ENOMEM;
	}

	cpumask_and(pd->cpumask.cbcpu, cbcpumask, cpu_online_mask);
	return 0;
}