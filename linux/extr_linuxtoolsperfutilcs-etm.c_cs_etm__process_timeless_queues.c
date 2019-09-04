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
struct cs_etm_queue {int tid; int /*<<< orphan*/  time; } ;
struct auxtrace_queues {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct cs_etm_auxtrace {struct auxtrace_queues queues; } ;
struct auxtrace_queue {struct cs_etm_queue* priv; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  cs_etm__run_decoder (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__set_pid_tid_cpu (struct cs_etm_auxtrace*,struct auxtrace_queue*) ; 

__attribute__((used)) static int cs_etm__process_timeless_queues(struct cs_etm_auxtrace *etm,
					   pid_t tid, u64 time_)
{
	unsigned int i;
	struct auxtrace_queues *queues = &etm->queues;

	for (i = 0; i < queues->nr_queues; i++) {
		struct auxtrace_queue *queue = &etm->queues.queue_array[i];
		struct cs_etm_queue *etmq = queue->priv;

		if (etmq && ((tid == -1) || (etmq->tid == tid))) {
			etmq->time = time_;
			cs_etm__set_pid_tid_cpu(etm, queue);
			cs_etm__run_decoder(etmq);
		}
	}

	return 0;
}