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
struct io_ring_ctx {int nr_user_bufs; struct io_mapped_ubuf* user_bufs; int /*<<< orphan*/  user; scalar_t__ account_mem; } ;
struct io_mapped_ubuf {int nr_bvecs; TYPE_1__* bvec; } ;
struct TYPE_2__ {int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  io_unaccount_mem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct io_mapped_ubuf*) ; 
 int /*<<< orphan*/  kvfree (TYPE_1__*) ; 
 int /*<<< orphan*/  put_user_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_sqe_buffer_unregister(struct io_ring_ctx *ctx)
{
	int i, j;

	if (!ctx->user_bufs)
		return -ENXIO;

	for (i = 0; i < ctx->nr_user_bufs; i++) {
		struct io_mapped_ubuf *imu = &ctx->user_bufs[i];

		for (j = 0; j < imu->nr_bvecs; j++)
			put_user_page(imu->bvec[j].bv_page);

		if (ctx->account_mem)
			io_unaccount_mem(ctx->user, imu->nr_bvecs);
		kvfree(imu->bvec);
		imu->nr_bvecs = 0;
	}

	kfree(ctx->user_bufs);
	ctx->user_bufs = NULL;
	ctx->nr_user_bufs = 0;
	return 0;
}