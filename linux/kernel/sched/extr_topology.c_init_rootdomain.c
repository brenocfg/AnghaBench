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
struct root_domain {int rto_cpu; int /*<<< orphan*/  span; int /*<<< orphan*/  online; int /*<<< orphan*/  dlo_mask; int /*<<< orphan*/  rto_mask; int /*<<< orphan*/  cpudl; int /*<<< orphan*/  cpupri; int /*<<< orphan*/  dl_bw; int /*<<< orphan*/  rto_push_work; int /*<<< orphan*/  rto_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpudl_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ cpudl_init (int /*<<< orphan*/ *) ; 
 scalar_t__ cpupri_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dl_bw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rto_push_irq_work_func ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_rootdomain(struct root_domain *rd)
{
	if (!zalloc_cpumask_var(&rd->span, GFP_KERNEL))
		goto out;
	if (!zalloc_cpumask_var(&rd->online, GFP_KERNEL))
		goto free_span;
	if (!zalloc_cpumask_var(&rd->dlo_mask, GFP_KERNEL))
		goto free_online;
	if (!zalloc_cpumask_var(&rd->rto_mask, GFP_KERNEL))
		goto free_dlo_mask;

#ifdef HAVE_RT_PUSH_IPI
	rd->rto_cpu = -1;
	raw_spin_lock_init(&rd->rto_lock);
	init_irq_work(&rd->rto_push_work, rto_push_irq_work_func);
#endif

	init_dl_bw(&rd->dl_bw);
	if (cpudl_init(&rd->cpudl) != 0)
		goto free_rto_mask;

	if (cpupri_init(&rd->cpupri) != 0)
		goto free_cpudl;
	return 0;

free_cpudl:
	cpudl_cleanup(&rd->cpudl);
free_rto_mask:
	free_cpumask_var(rd->rto_mask);
free_dlo_mask:
	free_cpumask_var(rd->dlo_mask);
free_online:
	free_cpumask_var(rd->online);
free_span:
	free_cpumask_var(rd->span);
out:
	return -ENOMEM;
}