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
struct intel_pt_queue {int sync_switch; } ;
struct TYPE_2__ {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct intel_pt {int sync_switch; TYPE_1__ queues; } ;
struct auxtrace_queue {struct intel_pt_queue* priv; } ;

/* Variables and functions */

__attribute__((used)) static void intel_pt_enable_sync_switch(struct intel_pt *pt)
{
	unsigned int i;

	pt->sync_switch = true;

	for (i = 0; i < pt->queues.nr_queues; i++) {
		struct auxtrace_queue *queue = &pt->queues.queue_array[i];
		struct intel_pt_queue *ptq = queue->priv;

		if (ptq)
			ptq->sync_switch = true;
	}
}