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
struct xdp_md {scalar_t__ data_end; scalar_t__ data; } ;

/* Variables and functions */
 int XDP_PASS ; 
 int /*<<< orphan*/  check_syncookie (struct xdp_md*,void*,void*) ; 

int check_syncookie_xdp(struct xdp_md *ctx)
{
	check_syncookie(ctx, (void *)(long)ctx->data,
			(void *)(long)ctx->data_end);
	return XDP_PASS;
}