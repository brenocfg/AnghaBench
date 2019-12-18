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
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct io_rings {TYPE_1__ cq; } ;
struct io_ring_ctx {scalar_t__ cached_cq_tail; int /*<<< orphan*/  cq_fasync; int /*<<< orphan*/  cq_wait; struct io_rings* rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __io_commit_cqring(struct io_ring_ctx *ctx)
{
	struct io_rings *rings = ctx->rings;

	if (ctx->cached_cq_tail != READ_ONCE(rings->cq.tail)) {
		/* order cqe stores with ring update */
		smp_store_release(&rings->cq.tail, ctx->cached_cq_tail);

		if (wq_has_sleeper(&ctx->cq_wait)) {
			wake_up_interruptible(&ctx->cq_wait);
			kill_fasync(&ctx->cq_fasync, SIGIO, POLL_IN);
		}
	}
}