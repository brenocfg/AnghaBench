#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct io_ring_ctx {scalar_t__ cached_sq_head; scalar_t__ cached_cq_tail; TYPE_3__* rings; int /*<<< orphan*/  cq_wait; } ;
struct file {struct io_ring_ctx* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_5__ {int /*<<< orphan*/  head; } ;
struct TYPE_4__ {int /*<<< orphan*/  tail; } ;
struct TYPE_6__ {scalar_t__ sq_ring_entries; TYPE_2__ cq; TYPE_1__ sq; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static __poll_t io_uring_poll(struct file *file, poll_table *wait)
{
	struct io_ring_ctx *ctx = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &ctx->cq_wait, wait);
	/*
	 * synchronizes with barrier from wq_has_sleeper call in
	 * io_commit_cqring
	 */
	smp_rmb();
	if (READ_ONCE(ctx->rings->sq.tail) - ctx->cached_sq_head !=
	    ctx->rings->sq_ring_entries)
		mask |= EPOLLOUT | EPOLLWRNORM;
	if (READ_ONCE(ctx->rings->cq.head) != ctx->cached_cq_tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}