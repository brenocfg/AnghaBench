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
struct irq_desc {int /*<<< orphan*/  percpu_affinity; int /*<<< orphan*/  percpu_enabled; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

int irq_get_percpu_devid_partition(unsigned int irq, struct cpumask *affinity)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (!desc || !desc->percpu_enabled)
		return -EINVAL;

	if (affinity)
		cpumask_copy(affinity, desc->percpu_affinity);

	return 0;
}