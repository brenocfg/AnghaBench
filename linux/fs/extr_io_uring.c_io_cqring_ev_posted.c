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
struct io_ring_ctx {scalar_t__ cq_ev_fd; int /*<<< orphan*/  sqo_wait; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_cqring_ev_posted(struct io_ring_ctx *ctx)
{
	if (waitqueue_active(&ctx->wait))
		wake_up(&ctx->wait);
	if (waitqueue_active(&ctx->sqo_wait))
		wake_up(&ctx->sqo_wait);
	if (ctx->cq_ev_fd)
		eventfd_signal(ctx->cq_ev_fd, 1);
}