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
typedef  scalar_t__ u64 ;
struct kioctx {unsigned int tail; unsigned int nr_events; int completed_events; int /*<<< orphan*/  wait; int /*<<< orphan*/  completion_lock; int /*<<< orphan*/ * ring_pages; } ;
struct io_event {long res; long res2; unsigned int head; unsigned int tail; int /*<<< orphan*/  data; scalar_t__ obj; } ;
struct aio_ring {long res; long res2; unsigned int head; unsigned int tail; int /*<<< orphan*/  data; scalar_t__ obj; } ;
struct aio_kiocb {scalar_t__ ki_eventfd; int /*<<< orphan*/  ki_user_data; scalar_t__ ki_user_iocb; struct kioctx* ki_ctx; } ;

/* Variables and functions */
 unsigned int AIO_EVENTS_OFFSET ; 
 unsigned int AIO_EVENTS_PER_PAGE ; 
 int /*<<< orphan*/  eventfd_ctx_put (scalar_t__) ; 
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iocb_put (struct aio_kiocb*) ; 
 struct io_event* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct io_event*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  refill_reqs_available (struct kioctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aio_complete(struct aio_kiocb *iocb, long res, long res2)
{
	struct kioctx	*ctx = iocb->ki_ctx;
	struct aio_ring	*ring;
	struct io_event	*ev_page, *event;
	unsigned tail, pos, head;
	unsigned long	flags;

	/*
	 * Add a completion event to the ring buffer. Must be done holding
	 * ctx->completion_lock to prevent other code from messing with the tail
	 * pointer since we might be called from irq context.
	 */
	spin_lock_irqsave(&ctx->completion_lock, flags);

	tail = ctx->tail;
	pos = tail + AIO_EVENTS_OFFSET;

	if (++tail >= ctx->nr_events)
		tail = 0;

	ev_page = kmap_atomic(ctx->ring_pages[pos / AIO_EVENTS_PER_PAGE]);
	event = ev_page + pos % AIO_EVENTS_PER_PAGE;

	event->obj = (u64)(unsigned long)iocb->ki_user_iocb;
	event->data = iocb->ki_user_data;
	event->res = res;
	event->res2 = res2;

	kunmap_atomic(ev_page);
	flush_dcache_page(ctx->ring_pages[pos / AIO_EVENTS_PER_PAGE]);

	pr_debug("%p[%u]: %p: %p %Lx %lx %lx\n",
		 ctx, tail, iocb, iocb->ki_user_iocb, iocb->ki_user_data,
		 res, res2);

	/* after flagging the request as done, we
	 * must never even look at it again
	 */
	smp_wmb();	/* make event visible before updating tail */

	ctx->tail = tail;

	ring = kmap_atomic(ctx->ring_pages[0]);
	head = ring->head;
	ring->tail = tail;
	kunmap_atomic(ring);
	flush_dcache_page(ctx->ring_pages[0]);

	ctx->completed_events++;
	if (ctx->completed_events > 1)
		refill_reqs_available(ctx, head, tail);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	pr_debug("added to ring %p at [%u]\n", iocb, tail);

	/*
	 * Check if the user asked us to deliver the result through an
	 * eventfd. The eventfd_signal() function is safe to be called
	 * from IRQ context.
	 */
	if (iocb->ki_eventfd) {
		eventfd_signal(iocb->ki_eventfd, 1);
		eventfd_ctx_put(iocb->ki_eventfd);
	}

	/*
	 * We have to order our ring_info tail store above and test
	 * of the wait list below outside the wait lock.  This is
	 * like in wake_up_bit() where clearing a bit has to be
	 * ordered with the unlocked test.
	 */
	smp_mb();

	if (waitqueue_active(&ctx->wait))
		wake_up(&ctx->wait);
	iocb_put(iocb);
}