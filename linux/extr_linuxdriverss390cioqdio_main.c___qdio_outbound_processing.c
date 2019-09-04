#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timer; scalar_t__ pci_out_enabled; } ;
struct TYPE_6__ {TYPE_2__ out; } ;
struct qdio_q {TYPE_3__ u; TYPE_1__* irq_ptr; int /*<<< orphan*/  nr_buf_used; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ QDIO_IRQ_STATE_ACTIVE ; 
 scalar_t__ QDIO_ZFCP_QFMT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pci_out_supported (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_kick_handler (struct qdio_q*) ; 
 scalar_t__ qdio_outbound_q_done (struct qdio_q*) ; 
 scalar_t__ qdio_outbound_q_moved (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_tasklet_schedule (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 
 int /*<<< orphan*/  tasklet_outbound ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __qdio_outbound_processing(struct qdio_q *q)
{
	qperf_inc(q, tasklet_outbound);
	WARN_ON_ONCE(atomic_read(&q->nr_buf_used) < 0);

	if (qdio_outbound_q_moved(q))
		qdio_kick_handler(q);

	if (queue_type(q) == QDIO_ZFCP_QFMT)
		if (!pci_out_supported(q) && !qdio_outbound_q_done(q))
			goto sched;

	if (q->u.out.pci_out_enabled)
		return;

	/*
	 * Now we know that queue type is either qeth without pci enabled
	 * or HiperSockets. Make sure buffer switch from PRIMED to EMPTY
	 * is noticed and outbound_handler is called after some time.
	 */
	if (qdio_outbound_q_done(q))
		del_timer_sync(&q->u.out.timer);
	else
		if (!timer_pending(&q->u.out.timer) &&
		    likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE))
			mod_timer(&q->u.out.timer, jiffies + 10 * HZ);
	return;

sched:
	qdio_tasklet_schedule(q);
}