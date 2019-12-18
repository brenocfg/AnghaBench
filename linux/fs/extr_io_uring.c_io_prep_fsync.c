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
struct io_uring_sqe {scalar_t__ buf_index; scalar_t__ ioprio; scalar_t__ addr; } ;
struct io_ring_ctx {int flags; } ;
struct io_kiocb {int /*<<< orphan*/  file; struct io_ring_ctx* ctx; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int IORING_SETUP_IOPOLL ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_prep_fsync(struct io_kiocb *req, const struct io_uring_sqe *sqe)
{
	struct io_ring_ctx *ctx = req->ctx;

	if (!req->file)
		return -EBADF;

	if (unlikely(ctx->flags & IORING_SETUP_IOPOLL))
		return -EINVAL;
	if (unlikely(sqe->addr || sqe->ioprio || sqe->buf_index))
		return -EINVAL;

	return 0;
}