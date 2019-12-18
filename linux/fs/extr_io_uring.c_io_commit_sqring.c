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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct io_rings {TYPE_1__ sq; } ;
struct io_ring_ctx {scalar_t__ cached_sq_head; struct io_rings* rings; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void io_commit_sqring(struct io_ring_ctx *ctx)
{
	struct io_rings *rings = ctx->rings;

	if (ctx->cached_sq_head != READ_ONCE(rings->sq.head)) {
		/*
		 * Ensure any loads from the SQEs are done at this point,
		 * since once we write the new head, the application could
		 * write new data to them.
		 */
		smp_store_release(&rings->sq.head, ctx->cached_sq_head);
	}
}