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
struct intel_bts_queue {scalar_t__ tid; } ;
struct auxtrace_queues {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct intel_bts {struct auxtrace_queues queues; } ;
struct auxtrace_queue {struct intel_bts_queue* priv; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int intel_bts_flush_queue (struct intel_bts_queue*) ; 

__attribute__((used)) static int intel_bts_process_tid_exit(struct intel_bts *bts, pid_t tid)
{
	struct auxtrace_queues *queues = &bts->queues;
	unsigned int i;

	for (i = 0; i < queues->nr_queues; i++) {
		struct auxtrace_queue *queue = &bts->queues.queue_array[i];
		struct intel_bts_queue *btsq = queue->priv;

		if (btsq && btsq->tid == tid)
			return intel_bts_flush_queue(btsq);
	}
	return 0;
}