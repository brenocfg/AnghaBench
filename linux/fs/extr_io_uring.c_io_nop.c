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
struct io_ring_ctx {int flags; } ;
struct io_kiocb {struct io_ring_ctx* ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int IORING_SETUP_IOPOLL ; 
 int /*<<< orphan*/  io_cqring_add_event (struct io_ring_ctx*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  io_put_req (struct io_kiocb*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_nop(struct io_kiocb *req, u64 user_data)
{
	struct io_ring_ctx *ctx = req->ctx;
	long err = 0;

	if (unlikely(ctx->flags & IORING_SETUP_IOPOLL))
		return -EINVAL;

	io_cqring_add_event(ctx, user_data, err);
	io_put_req(req);
	return 0;
}