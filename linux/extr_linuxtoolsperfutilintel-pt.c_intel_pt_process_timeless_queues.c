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
typedef  int /*<<< orphan*/  u64 ;
struct intel_pt_queue {int tid; int /*<<< orphan*/  time; } ;
struct auxtrace_queues {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct intel_pt {struct auxtrace_queues queues; } ;
struct auxtrace_queue {struct intel_pt_queue* priv; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_run_decoder (struct intel_pt_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_pt_set_pid_tid_cpu (struct intel_pt*,struct auxtrace_queue*) ; 

__attribute__((used)) static int intel_pt_process_timeless_queues(struct intel_pt *pt, pid_t tid,
					    u64 time_)
{
	struct auxtrace_queues *queues = &pt->queues;
	unsigned int i;
	u64 ts = 0;

	for (i = 0; i < queues->nr_queues; i++) {
		struct auxtrace_queue *queue = &pt->queues.queue_array[i];
		struct intel_pt_queue *ptq = queue->priv;

		if (ptq && (tid == -1 || ptq->tid == tid)) {
			ptq->time = time_;
			intel_pt_set_pid_tid_cpu(pt, queue);
			intel_pt_run_decoder(ptq, &ts);
		}
	}
	return 0;
}