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
struct parallel_data {int /*<<< orphan*/  squeue; int /*<<< orphan*/  pqueue; TYPE_1__ cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct parallel_data*) ; 

__attribute__((used)) static void padata_free_pd(struct parallel_data *pd)
{
	free_cpumask_var(pd->cpumask.pcpu);
	free_cpumask_var(pd->cpumask.cbcpu);
	free_percpu(pd->pqueue);
	free_percpu(pd->squeue);
	kfree(pd);
}