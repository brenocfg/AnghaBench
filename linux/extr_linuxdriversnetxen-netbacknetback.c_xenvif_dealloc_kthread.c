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
struct xenvif_queue {int /*<<< orphan*/  dealloc_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ tx_dealloc_work_todo (struct xenvif_queue*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xenvif_dealloc_kthread_should_stop (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_tx_dealloc_action (struct xenvif_queue*) ; 

int xenvif_dealloc_kthread(void *data)
{
	struct xenvif_queue *queue = data;

	for (;;) {
		wait_event_interruptible(queue->dealloc_wq,
					 tx_dealloc_work_todo(queue) ||
					 xenvif_dealloc_kthread_should_stop(queue));
		if (xenvif_dealloc_kthread_should_stop(queue))
			break;

		xenvif_tx_dealloc_action(queue);
		cond_resched();
	}

	/* Unmap anything remaining*/
	if (tx_dealloc_work_todo(queue))
		xenvif_tx_dealloc_action(queue);

	return 0;
}