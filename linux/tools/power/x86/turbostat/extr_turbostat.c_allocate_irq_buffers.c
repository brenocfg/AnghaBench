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
struct TYPE_2__ {scalar_t__ max_cpu_num; scalar_t__ num_cpus; } ;

/* Variables and functions */
 void* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  err (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * irq_column_2_cpu ; 
 int /*<<< orphan*/ * irqs_per_cpu ; 
 TYPE_1__ topo ; 

void allocate_irq_buffers(void)
{
	irq_column_2_cpu = calloc(topo.num_cpus, sizeof(int));
	if (irq_column_2_cpu == NULL)
		err(-1, "calloc %d", topo.num_cpus);

	irqs_per_cpu = calloc(topo.max_cpu_num + 1, sizeof(int));
	if (irqs_per_cpu == NULL)
		err(-1, "calloc %d", topo.max_cpu_num + 1);
}