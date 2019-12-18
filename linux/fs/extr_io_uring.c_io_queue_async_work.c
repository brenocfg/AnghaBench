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
struct io_ring_ctx {int /*<<< orphan*/ * sqo_wq; } ;
struct TYPE_6__ {int ki_flags; } ;
struct TYPE_5__ {TYPE_1__* sqe; } ;
struct io_kiocb {int /*<<< orphan*/  work; TYPE_3__ rw; TYPE_2__ submit; } ;
struct TYPE_4__ {int opcode; } ;

/* Variables and functions */
 int IOCB_DIRECT ; 
#define  IORING_OP_WRITEV 129 
#define  IORING_OP_WRITE_FIXED 128 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void io_queue_async_work(struct io_ring_ctx *ctx,
				       struct io_kiocb *req)
{
	int rw = 0;

	if (req->submit.sqe) {
		switch (req->submit.sqe->opcode) {
		case IORING_OP_WRITEV:
		case IORING_OP_WRITE_FIXED:
			rw = !(req->rw.ki_flags & IOCB_DIRECT);
			break;
		}
	}

	queue_work(ctx->sqo_wq[rw], &req->work);
}