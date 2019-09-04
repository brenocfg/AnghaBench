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
struct parallel_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cbcpu; int /*<<< orphan*/  pcpu; } ;
struct padata_instance {TYPE_1__ cpumask; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __padata_start (struct padata_instance*) ; 
 int /*<<< orphan*/  __padata_stop (struct padata_instance*) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct parallel_data* padata_alloc_pd (struct padata_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_replace (struct padata_instance*,struct parallel_data*) ; 
 int padata_validate_cpumask (struct padata_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __padata_set_cpumasks(struct padata_instance *pinst,
				 cpumask_var_t pcpumask,
				 cpumask_var_t cbcpumask)
{
	int valid;
	struct parallel_data *pd;

	valid = padata_validate_cpumask(pinst, pcpumask);
	if (!valid) {
		__padata_stop(pinst);
		goto out_replace;
	}

	valid = padata_validate_cpumask(pinst, cbcpumask);
	if (!valid)
		__padata_stop(pinst);

out_replace:
	pd = padata_alloc_pd(pinst, pcpumask, cbcpumask);
	if (!pd)
		return -ENOMEM;

	cpumask_copy(pinst->cpumask.pcpu, pcpumask);
	cpumask_copy(pinst->cpumask.cbcpu, cbcpumask);

	padata_replace(pinst, pd);

	if (valid)
		__padata_start(pinst);

	return 0;
}