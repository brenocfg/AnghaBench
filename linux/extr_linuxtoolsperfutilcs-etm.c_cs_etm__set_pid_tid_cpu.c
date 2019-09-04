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
struct cs_etm_queue {int tid; TYPE_1__* thread; int /*<<< orphan*/  cpu; int /*<<< orphan*/  pid; } ;
struct cs_etm_auxtrace {int /*<<< orphan*/  machine; } ;
struct auxtrace_queue {int tid; int cpu; struct cs_etm_queue* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  pid_; } ;

/* Variables and functions */
 TYPE_1__* machine__find_thread (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs_etm__set_pid_tid_cpu(struct cs_etm_auxtrace *etm,
				    struct auxtrace_queue *queue)
{
	struct cs_etm_queue *etmq = queue->priv;

	/* CPU-wide tracing isn't supported yet */
	if (queue->tid == -1)
		return;

	if ((!etmq->thread) && (etmq->tid != -1))
		etmq->thread = machine__find_thread(etm->machine, -1,
						    etmq->tid);

	if (etmq->thread) {
		etmq->pid = etmq->thread->pid_;
		if (queue->cpu == -1)
			etmq->cpu = etmq->thread->cpu;
	}
}