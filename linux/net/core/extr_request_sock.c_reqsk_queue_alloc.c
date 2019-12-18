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
struct TYPE_2__ {scalar_t__ qlen; int /*<<< orphan*/ * rskq_rst_tail; int /*<<< orphan*/ * rskq_rst_head; int /*<<< orphan*/  lock; } ;
struct request_sock_queue {int /*<<< orphan*/ * rskq_accept_head; TYPE_1__ fastopenq; int /*<<< orphan*/  rskq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void reqsk_queue_alloc(struct request_sock_queue *queue)
{
	spin_lock_init(&queue->rskq_lock);

	spin_lock_init(&queue->fastopenq.lock);
	queue->fastopenq.rskq_rst_head = NULL;
	queue->fastopenq.rskq_rst_tail = NULL;
	queue->fastopenq.qlen = 0;

	queue->rskq_accept_head = NULL;
}