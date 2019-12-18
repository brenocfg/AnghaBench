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
struct tmpmasks {int /*<<< orphan*/  delmask; int /*<<< orphan*/  addmask; int /*<<< orphan*/  new_cpus; } ;
struct cpuset {int /*<<< orphan*/  subparts_cpus; int /*<<< orphan*/  effective_cpus; int /*<<< orphan*/  cpus_allowed; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int alloc_cpumasks(struct cpuset *cs, struct tmpmasks *tmp)
{
	cpumask_var_t *pmask1, *pmask2, *pmask3;

	if (cs) {
		pmask1 = &cs->cpus_allowed;
		pmask2 = &cs->effective_cpus;
		pmask3 = &cs->subparts_cpus;
	} else {
		pmask1 = &tmp->new_cpus;
		pmask2 = &tmp->addmask;
		pmask3 = &tmp->delmask;
	}

	if (!zalloc_cpumask_var(pmask1, GFP_KERNEL))
		return -ENOMEM;

	if (!zalloc_cpumask_var(pmask2, GFP_KERNEL))
		goto free_one;

	if (!zalloc_cpumask_var(pmask3, GFP_KERNEL))
		goto free_two;

	return 0;

free_two:
	free_cpumask_var(*pmask2);
free_one:
	free_cpumask_var(*pmask1);
	return -ENOMEM;
}