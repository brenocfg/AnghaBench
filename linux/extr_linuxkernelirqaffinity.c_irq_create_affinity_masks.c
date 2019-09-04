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
struct irq_affinity {int pre_vectors; int post_vectors; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * alloc_node_to_cpumask () ; 
 int /*<<< orphan*/  build_node_to_cpumask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpu_present_mask ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_node_to_cpumask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int irq_build_affinity_masks (struct irq_affinity const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpumask*) ; 
 int /*<<< orphan*/  irq_default_affinity ; 
 struct cpumask* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct cpumask *
irq_create_affinity_masks(int nvecs, const struct irq_affinity *affd)
{
	int affvecs = nvecs - affd->pre_vectors - affd->post_vectors;
	int curvec, usedvecs;
	cpumask_var_t nmsk, npresmsk, *node_to_cpumask;
	struct cpumask *masks = NULL;

	/*
	 * If there aren't any vectors left after applying the pre/post
	 * vectors don't bother with assigning affinity.
	 */
	if (nvecs == affd->pre_vectors + affd->post_vectors)
		return NULL;

	if (!zalloc_cpumask_var(&nmsk, GFP_KERNEL))
		return NULL;

	if (!zalloc_cpumask_var(&npresmsk, GFP_KERNEL))
		goto outcpumsk;

	node_to_cpumask = alloc_node_to_cpumask();
	if (!node_to_cpumask)
		goto outnpresmsk;

	masks = kcalloc(nvecs, sizeof(*masks), GFP_KERNEL);
	if (!masks)
		goto outnodemsk;

	/* Fill out vectors at the beginning that don't need affinity */
	for (curvec = 0; curvec < affd->pre_vectors; curvec++)
		cpumask_copy(masks + curvec, irq_default_affinity);

	/* Stabilize the cpumasks */
	get_online_cpus();
	build_node_to_cpumask(node_to_cpumask);

	/* Spread on present CPUs starting from affd->pre_vectors */
	usedvecs = irq_build_affinity_masks(affd, curvec, affvecs,
					    node_to_cpumask, cpu_present_mask,
					    nmsk, masks);

	/*
	 * Spread on non present CPUs starting from the next vector to be
	 * handled. If the spreading of present CPUs already exhausted the
	 * vector space, assign the non present CPUs to the already spread
	 * out vectors.
	 */
	if (usedvecs >= affvecs)
		curvec = affd->pre_vectors;
	else
		curvec = affd->pre_vectors + usedvecs;
	cpumask_andnot(npresmsk, cpu_possible_mask, cpu_present_mask);
	usedvecs += irq_build_affinity_masks(affd, curvec, affvecs,
					     node_to_cpumask, npresmsk,
					     nmsk, masks);
	put_online_cpus();

	/* Fill out vectors at the end that don't need affinity */
	if (usedvecs >= affvecs)
		curvec = affd->pre_vectors + affvecs;
	else
		curvec = affd->pre_vectors + usedvecs;
	for (; curvec < nvecs; curvec++)
		cpumask_copy(masks + curvec, irq_default_affinity);

outnodemsk:
	free_node_to_cpumask(node_to_cpumask);
outnpresmsk:
	free_cpumask_var(npresmsk);
outcpumsk:
	free_cpumask_var(nmsk);
	return masks;
}