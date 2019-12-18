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
struct sched_group {int /*<<< orphan*/  ref; } ;
struct sched_domain {struct sched_domain* child; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_size () ; 
 struct sched_group* kzalloc_node (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_domain_span (struct sched_domain*) ; 
 struct cpumask* sched_group_span (struct sched_group*) ; 

__attribute__((used)) static struct sched_group *
build_group_from_child_sched_domain(struct sched_domain *sd, int cpu)
{
	struct sched_group *sg;
	struct cpumask *sg_span;

	sg = kzalloc_node(sizeof(struct sched_group) + cpumask_size(),
			GFP_KERNEL, cpu_to_node(cpu));

	if (!sg)
		return NULL;

	sg_span = sched_group_span(sg);
	if (sd->child)
		cpumask_copy(sg_span, sched_domain_span(sd->child));
	else
		cpumask_copy(sg_span, sched_domain_span(sd));

	atomic_inc(&sg->ref);
	return sg;
}