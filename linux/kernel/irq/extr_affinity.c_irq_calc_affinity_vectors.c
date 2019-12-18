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
struct irq_affinity {unsigned int pre_vectors; unsigned int post_vectors; scalar_t__ calc_sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_possible_mask ; 
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

unsigned int irq_calc_affinity_vectors(unsigned int minvec, unsigned int maxvec,
				       const struct irq_affinity *affd)
{
	unsigned int resv = affd->pre_vectors + affd->post_vectors;
	unsigned int set_vecs;

	if (resv > minvec)
		return 0;

	if (affd->calc_sets) {
		set_vecs = maxvec - resv;
	} else {
		get_online_cpus();
		set_vecs = cpumask_weight(cpu_possible_mask);
		put_online_cpus();
	}

	return resv + min(set_vecs, maxvec - resv);
}