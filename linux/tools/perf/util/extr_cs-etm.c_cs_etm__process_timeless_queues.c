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
struct cs_etm_traceid_queue {int tid; } ;
struct cs_etm_queue {int dummy; } ;
struct auxtrace_queues {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct cs_etm_auxtrace {struct auxtrace_queues queues; } ;
struct auxtrace_queue {struct cs_etm_queue* priv; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_PER_THREAD_TRACEID ; 
 struct cs_etm_traceid_queue* cs_etm__etmq_get_traceid_queue (struct cs_etm_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm__run_decoder (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__set_pid_tid_cpu (struct cs_etm_auxtrace*,struct cs_etm_traceid_queue*) ; 

__attribute__((used)) static int cs_etm__process_timeless_queues(struct cs_etm_auxtrace *etm,
					   pid_t tid)
{
	unsigned int i;
	struct auxtrace_queues *queues = &etm->queues;

	for (i = 0; i < queues->nr_queues; i++) {
		struct auxtrace_queue *queue = &etm->queues.queue_array[i];
		struct cs_etm_queue *etmq = queue->priv;
		struct cs_etm_traceid_queue *tidq;

		if (!etmq)
			continue;

		tidq = cs_etm__etmq_get_traceid_queue(etmq,
						CS_ETM_PER_THREAD_TRACEID);

		if (!tidq)
			continue;

		if ((tid == -1) || (tidq->tid == tid)) {
			cs_etm__set_pid_tid_cpu(etm, tidq);
			cs_etm__run_decoder(etmq);
		}
	}

	return 0;
}