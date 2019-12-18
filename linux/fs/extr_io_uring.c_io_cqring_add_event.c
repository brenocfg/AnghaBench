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
typedef  int /*<<< orphan*/  u64 ;
struct io_ring_ctx {int /*<<< orphan*/  completion_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_commit_cqring (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_cqring_ev_posted (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_cqring_fill_event (struct io_ring_ctx*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void io_cqring_add_event(struct io_ring_ctx *ctx, u64 user_data,
				long res)
{
	unsigned long flags;

	spin_lock_irqsave(&ctx->completion_lock, flags);
	io_cqring_fill_event(ctx, user_data, res);
	io_commit_cqring(ctx);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	io_cqring_ev_posted(ctx);
}