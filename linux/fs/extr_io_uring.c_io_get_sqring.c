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
typedef  int /*<<< orphan*/  u32 ;
struct sqe_submit {unsigned int index; unsigned int sequence; int /*<<< orphan*/ * sqe; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct io_rings {int /*<<< orphan*/  sq_dropped; TYPE_1__ sq; } ;
struct io_ring_ctx {unsigned int cached_sq_head; unsigned int sq_mask; unsigned int sq_entries; int /*<<< orphan*/  cached_sq_dropped; int /*<<< orphan*/ * sq_sqes; int /*<<< orphan*/ * sq_array; struct io_rings* rings; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int smp_load_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool io_get_sqring(struct io_ring_ctx *ctx, struct sqe_submit *s)
{
	struct io_rings *rings = ctx->rings;
	u32 *sq_array = ctx->sq_array;
	unsigned head;

	/*
	 * The cached sq head (or cq tail) serves two purposes:
	 *
	 * 1) allows us to batch the cost of updating the user visible
	 *    head updates.
	 * 2) allows the kernel side to track the head on its own, even
	 *    though the application is the one updating it.
	 */
	head = ctx->cached_sq_head;
	/* make sure SQ entry isn't read before tail */
	if (head == smp_load_acquire(&rings->sq.tail))
		return false;

	head = READ_ONCE(sq_array[head & ctx->sq_mask]);
	if (head < ctx->sq_entries) {
		s->index = head;
		s->sqe = &ctx->sq_sqes[head];
		s->sequence = ctx->cached_sq_head;
		ctx->cached_sq_head++;
		return true;
	}

	/* drop invalid entries */
	ctx->cached_sq_head++;
	ctx->cached_sq_dropped++;
	WRITE_ONCE(rings->sq_dropped, ctx->cached_sq_dropped);
	return false;
}