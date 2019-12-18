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
struct kioctx {int /*<<< orphan*/  completion_lock; int /*<<< orphan*/  tail; int /*<<< orphan*/ * ring_pages; scalar_t__ completed_events; } ;
struct aio_ring {unsigned int head; } ;

/* Variables and functions */
 struct aio_ring* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct aio_ring*) ; 
 int /*<<< orphan*/  refill_reqs_available (struct kioctx*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_refill_reqs_available(struct kioctx *ctx)
{
	spin_lock_irq(&ctx->completion_lock);
	if (ctx->completed_events) {
		struct aio_ring *ring;
		unsigned head;

		/* Access of ring->head may race with aio_read_events_ring()
		 * here, but that's okay since whether we read the old version
		 * or the new version, and either will be valid.  The important
		 * part is that head cannot pass tail since we prevent
		 * aio_complete() from updating tail by holding
		 * ctx->completion_lock.  Even if head is invalid, the check
		 * against ctx->completed_events below will make sure we do the
		 * safe/right thing.
		 */
		ring = kmap_atomic(ctx->ring_pages[0]);
		head = ring->head;
		kunmap_atomic(ring);

		refill_reqs_available(ctx, head, ctx->tail);
	}

	spin_unlock_irq(&ctx->completion_lock);
}