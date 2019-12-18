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
struct io_ring_ctx {scalar_t__ nr_user_files; int /*<<< orphan*/ * user_files; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  __io_sqe_files_unregister (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_sqe_files_unregister(struct io_ring_ctx *ctx)
{
	if (!ctx->user_files)
		return -ENXIO;

	__io_sqe_files_unregister(ctx);
	kfree(ctx->user_files);
	ctx->user_files = NULL;
	ctx->nr_user_files = 0;
	return 0;
}