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
struct irq_affinity_desc {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __irq_build_affinity_masks (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct irq_affinity_desc*) ; 
 int /*<<< orphan*/ * alloc_node_to_cpumask () ; 
 int /*<<< orphan*/  build_node_to_cpumask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpu_present_mask ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_node_to_cpumask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irq_build_affinity_masks(unsigned int startvec, unsigned int numvecs,
				    unsigned int firstvec,
				    struct irq_affinity_desc *masks)
{
	unsigned int curvec = startvec, nr_present = 0, nr_others = 0;
	cpumask_var_t *node_to_cpumask;
	cpumask_var_t nmsk, npresmsk;
	int ret = -ENOMEM;

	if (!zalloc_cpumask_var(&nmsk, GFP_KERNEL))
		return ret;

	if (!zalloc_cpumask_var(&npresmsk, GFP_KERNEL))
		goto fail_nmsk;

	node_to_cpumask = alloc_node_to_cpumask();
	if (!node_to_cpumask)
		goto fail_npresmsk;

	/* Stabilize the cpumasks */
	get_online_cpus();
	build_node_to_cpumask(node_to_cpumask);

	/* Spread on present CPUs starting from affd->pre_vectors */
	ret = __irq_build_affinity_masks(curvec, numvecs, firstvec,
					 node_to_cpumask, cpu_present_mask,
					 nmsk, masks);
	if (ret < 0)
		goto fail_build_affinity;
	nr_present = ret;

	/*
	 * Spread on non present CPUs starting from the next vector to be
	 * handled. If the spreading of present CPUs already exhausted the
	 * vector space, assign the non present CPUs to the already spread
	 * out vectors.
	 */
	if (nr_present >= numvecs)
		curvec = firstvec;
	else
		curvec = firstvec + nr_present;
	cpumask_andnot(npresmsk, cpu_possible_mask, cpu_present_mask);
	ret = __irq_build_affinity_masks(curvec, numvecs, firstvec,
					 node_to_cpumask, npresmsk, nmsk,
					 masks);
	if (ret >= 0)
		nr_others = ret;

 fail_build_affinity:
	put_online_cpus();

	if (ret >= 0)
		WARN_ON(nr_present + nr_others < numvecs);

	free_node_to_cpumask(node_to_cpumask);

 fail_npresmsk:
	free_cpumask_var(npresmsk);

 fail_nmsk:
	free_cpumask_var(nmsk);
	return ret < 0 ? ret : 0;
}