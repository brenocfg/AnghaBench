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
typedef  long u64 ;
struct io_uring_cqe {int /*<<< orphan*/  flags; int /*<<< orphan*/  res; int /*<<< orphan*/  user_data; } ;
struct io_ring_ctx {int /*<<< orphan*/  cached_cq_overflow; TYPE_1__* rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,long) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct io_uring_cqe* io_get_cqring (struct io_ring_ctx*) ; 

__attribute__((used)) static void io_cqring_fill_event(struct io_ring_ctx *ctx, u64 ki_user_data,
				 long res)
{
	struct io_uring_cqe *cqe;

	/*
	 * If we can't get a cq entry, userspace overflowed the
	 * submission (by quite a lot). Increment the overflow count in
	 * the ring.
	 */
	cqe = io_get_cqring(ctx);
	if (cqe) {
		WRITE_ONCE(cqe->user_data, ki_user_data);
		WRITE_ONCE(cqe->res, res);
		WRITE_ONCE(cqe->flags, 0);
	} else {
		WRITE_ONCE(ctx->rings->cq_overflow,
				atomic_inc_return(&ctx->cached_cq_overflow));
	}
}