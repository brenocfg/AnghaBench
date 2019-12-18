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
struct sched_dl_entity {int /*<<< orphan*/  deadline; } ;
struct task_struct {int /*<<< orphan*/  cpus_ptr; struct sched_dl_entity dl; } ;
struct cpumask {int dummy; } ;
struct cpudl {TYPE_1__* elements; int /*<<< orphan*/  free_cpus; } ;
struct TYPE_2__ {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_present (int) ; 
 int cpudl_maximum (struct cpudl*) ; 
 scalar_t__ cpumask_and (struct cpumask*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dl_time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cpudl_find(struct cpudl *cp, struct task_struct *p,
	       struct cpumask *later_mask)
{
	const struct sched_dl_entity *dl_se = &p->dl;

	if (later_mask &&
	    cpumask_and(later_mask, cp->free_cpus, p->cpus_ptr)) {
		return 1;
	} else {
		int best_cpu = cpudl_maximum(cp);

		WARN_ON(best_cpu != -1 && !cpu_present(best_cpu));

		if (cpumask_test_cpu(best_cpu, p->cpus_ptr) &&
		    dl_time_before(dl_se->deadline, cp->elements[0].dl)) {
			if (later_mask)
				cpumask_set_cpu(best_cpu, later_mask);

			return 1;
		}
	}
	return 0;
}