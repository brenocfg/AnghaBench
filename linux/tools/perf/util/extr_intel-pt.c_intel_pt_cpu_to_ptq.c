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
struct intel_pt_queue {int dummy; } ;
struct TYPE_4__ {unsigned int nr_queues; TYPE_1__* queue_array; } ;
struct intel_pt {TYPE_2__ queues; } ;
struct TYPE_3__ {int cpu; struct intel_pt_queue* priv; } ;

/* Variables and functions */

__attribute__((used)) static struct intel_pt_queue *intel_pt_cpu_to_ptq(struct intel_pt *pt, int cpu)
{
	unsigned i, j;

	if (cpu < 0 || !pt->queues.nr_queues)
		return NULL;

	if ((unsigned)cpu >= pt->queues.nr_queues)
		i = pt->queues.nr_queues - 1;
	else
		i = cpu;

	if (pt->queues.queue_array[i].cpu == cpu)
		return pt->queues.queue_array[i].priv;

	for (j = 0; i > 0; j++) {
		if (pt->queues.queue_array[--i].cpu == cpu)
			return pt->queues.queue_array[i].priv;
	}

	for (; j < pt->queues.nr_queues; j++) {
		if (pt->queues.queue_array[j].cpu == cpu)
			return pt->queues.queue_array[j].priv;
	}

	return NULL;
}