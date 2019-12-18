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
struct io_uring_cqe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct io_rings {unsigned int cq_ring_entries; struct io_uring_cqe* cqes; TYPE_1__ cq; } ;
struct io_ring_ctx {unsigned int cached_cq_tail; unsigned int cq_mask; struct io_rings* rings; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct io_uring_cqe *io_get_cqring(struct io_ring_ctx *ctx)
{
	struct io_rings *rings = ctx->rings;
	unsigned tail;

	tail = ctx->cached_cq_tail;
	/*
	 * writes to the cq entry need to come after reading head; the
	 * control dependency is enough as we're using WRITE_ONCE to
	 * fill the cq entry
	 */
	if (tail - READ_ONCE(rings->cq.head) == rings->cq_ring_entries)
		return NULL;

	ctx->cached_cq_tail++;
	return &rings->cqes[tail & ctx->cq_mask];
}