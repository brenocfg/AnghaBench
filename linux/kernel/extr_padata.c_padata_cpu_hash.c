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
struct TYPE_2__ {int /*<<< orphan*/  pcpu; } ;
struct parallel_data {TYPE_1__ cpumask; } ;

/* Variables and functions */
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 int padata_index_to_cpu (struct parallel_data*,int) ; 

__attribute__((used)) static int padata_cpu_hash(struct parallel_data *pd, unsigned int seq_nr)
{
	/*
	 * Hash the sequence numbers to the cpus by taking
	 * seq_nr mod. number of cpus in use.
	 */
	int cpu_index = seq_nr % cpumask_weight(pd->cpumask.pcpu);

	return padata_index_to_cpu(pd, cpu_index);
}