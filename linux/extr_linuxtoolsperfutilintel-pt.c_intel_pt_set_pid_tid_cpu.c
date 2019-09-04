#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_queue {int tid; TYPE_1__* thread; int /*<<< orphan*/  cpu; int /*<<< orphan*/  pid; } ;
struct intel_pt {int /*<<< orphan*/  machine; scalar_t__ have_sched_switch; } ;
struct auxtrace_queue {int tid; int cpu; struct intel_pt_queue* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  pid_; } ;

/* Variables and functions */
 TYPE_1__* machine__find_thread (int /*<<< orphan*/ ,int,int) ; 
 int machine__get_current_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__zput (TYPE_1__*) ; 

__attribute__((used)) static void intel_pt_set_pid_tid_cpu(struct intel_pt *pt,
				     struct auxtrace_queue *queue)
{
	struct intel_pt_queue *ptq = queue->priv;

	if (queue->tid == -1 || pt->have_sched_switch) {
		ptq->tid = machine__get_current_tid(pt->machine, ptq->cpu);
		thread__zput(ptq->thread);
	}

	if (!ptq->thread && ptq->tid != -1)
		ptq->thread = machine__find_thread(pt->machine, -1, ptq->tid);

	if (ptq->thread) {
		ptq->pid = ptq->thread->pid_;
		if (queue->cpu == -1)
			ptq->cpu = ptq->thread->cpu;
	}
}