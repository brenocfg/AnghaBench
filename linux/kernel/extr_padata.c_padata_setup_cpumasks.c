#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct workqueue_attrs {int /*<<< orphan*/  cpumask; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcpu; int /*<<< orphan*/  cbcpu; } ;
struct parallel_data {TYPE_2__ cpumask; TYPE_1__* pinst; } ;
struct cpumask {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parallel_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct workqueue_attrs* alloc_workqueue_attrs () ; 
 int apply_workqueue_attrs (int /*<<< orphan*/ ,struct workqueue_attrs*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_workqueue_attrs (struct workqueue_attrs*) ; 

__attribute__((used)) static int padata_setup_cpumasks(struct parallel_data *pd,
				 const struct cpumask *pcpumask,
				 const struct cpumask *cbcpumask)
{
	struct workqueue_attrs *attrs;
	int err = -ENOMEM;

	if (!alloc_cpumask_var(&pd->cpumask.pcpu, GFP_KERNEL))
		goto out;
	cpumask_and(pd->cpumask.pcpu, pcpumask, cpu_online_mask);

	if (!alloc_cpumask_var(&pd->cpumask.cbcpu, GFP_KERNEL))
		goto free_pcpu_mask;
	cpumask_and(pd->cpumask.cbcpu, cbcpumask, cpu_online_mask);

	attrs = alloc_workqueue_attrs();
	if (!attrs)
		goto free_cbcpu_mask;

	/* Restrict parallel_wq workers to pd->cpumask.pcpu. */
	cpumask_copy(attrs->cpumask, pd->cpumask.pcpu);
	err = apply_workqueue_attrs(pd->pinst->parallel_wq, attrs);
	free_workqueue_attrs(attrs);
	if (err < 0)
		goto free_cbcpu_mask;

	return 0;

free_cbcpu_mask:
	free_cpumask_var(pd->cpumask.cbcpu);
free_pcpu_mask:
	free_cpumask_var(pd->cpumask.pcpu);
out:
	return err;
}