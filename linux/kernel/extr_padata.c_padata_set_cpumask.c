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
struct TYPE_2__ {struct cpumask* pcpu; struct cpumask* cbcpu; } ;
struct padata_instance {int /*<<< orphan*/  lock; TYPE_1__ cpumask; } ;
struct cpumask {int dummy; } ;
typedef  struct cpumask* cpumask_var_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PADATA_CPU_PARALLEL 129 
#define  PADATA_CPU_SERIAL 128 
 int __padata_set_cpumasks (struct padata_instance*,struct cpumask*,struct cpumask*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

int padata_set_cpumask(struct padata_instance *pinst, int cpumask_type,
		       cpumask_var_t cpumask)
{
	struct cpumask *serial_mask, *parallel_mask;
	int err = -EINVAL;

	mutex_lock(&pinst->lock);
	get_online_cpus();

	switch (cpumask_type) {
	case PADATA_CPU_PARALLEL:
		serial_mask = pinst->cpumask.cbcpu;
		parallel_mask = cpumask;
		break;
	case PADATA_CPU_SERIAL:
		parallel_mask = pinst->cpumask.pcpu;
		serial_mask = cpumask;
		break;
	default:
		 goto out;
	}

	err =  __padata_set_cpumasks(pinst, parallel_mask, serial_mask);

out:
	put_online_cpus();
	mutex_unlock(&pinst->lock);

	return err;
}