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
struct io_ring_ctx {int /*<<< orphan*/  poll_list; } ;

/* Variables and functions */
 int io_do_iopoll (struct io_ring_ctx*,unsigned int*,long) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  need_resched () ; 

__attribute__((used)) static int io_iopoll_getevents(struct io_ring_ctx *ctx, unsigned int *nr_events,
				long min)
{
	while (!list_empty(&ctx->poll_list) && !need_resched()) {
		int ret;

		ret = io_do_iopoll(ctx, nr_events, min);
		if (ret < 0)
			return ret;
		if (!min || *nr_events >= min)
			return 0;
	}

	return 1;
}