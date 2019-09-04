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
struct eventfd_ctx {int flags; int count; } ;
typedef  int __u64 ;

/* Variables and functions */
 int EFD_SEMAPHORE ; 

__attribute__((used)) static void eventfd_ctx_do_read(struct eventfd_ctx *ctx, __u64 *cnt)
{
	*cnt = (ctx->flags & EFD_SEMAPHORE) ? 1 : ctx->count;
	ctx->count -= *cnt;
}