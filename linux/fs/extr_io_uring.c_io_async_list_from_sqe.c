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
struct io_uring_sqe {int opcode; } ;
struct io_ring_ctx {struct async_list* pending_async; } ;
struct async_list {int dummy; } ;

/* Variables and functions */
#define  IORING_OP_READV 131 
#define  IORING_OP_READ_FIXED 130 
#define  IORING_OP_WRITEV 129 
#define  IORING_OP_WRITE_FIXED 128 
 size_t READ ; 
 size_t WRITE ; 

__attribute__((used)) static struct async_list *io_async_list_from_sqe(struct io_ring_ctx *ctx,
						 const struct io_uring_sqe *sqe)
{
	switch (sqe->opcode) {
	case IORING_OP_READV:
	case IORING_OP_READ_FIXED:
		return &ctx->pending_async[READ];
	case IORING_OP_WRITEV:
	case IORING_OP_WRITE_FIXED:
		return &ctx->pending_async[WRITE];
	default:
		return NULL;
	}
}