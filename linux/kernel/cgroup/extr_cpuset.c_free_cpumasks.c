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

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_cpumasks(struct cpuset *cs, struct tmpmasks *tmp)
{
	if (cs) {
		free_cpumask_var(cs->cpus_allowed);
		free_cpumask_var(cs->effective_cpus);
		free_cpumask_var(cs->subparts_cpus);
	}
	if (tmp) {
		free_cpumask_var(tmp->new_cpus);
		free_cpumask_var(tmp->addmask);
		free_cpumask_var(tmp->delmask);
	}
}