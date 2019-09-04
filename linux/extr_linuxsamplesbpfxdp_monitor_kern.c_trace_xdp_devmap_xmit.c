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
typedef  int /*<<< orphan*/  u32 ;
struct devmap_xmit_ctx {scalar_t__ drops; scalar_t__ err; scalar_t__ sent; } ;
struct datarec {int info; int /*<<< orphan*/  err; int /*<<< orphan*/  dropped; int /*<<< orphan*/  processed; } ;

/* Variables and functions */
 struct datarec* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devmap_xmit_cnt ; 

int trace_xdp_devmap_xmit(struct devmap_xmit_ctx *ctx)
{
	struct datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&devmap_xmit_cnt, &key);
	if (!rec)
		return 0;
	rec->processed += ctx->sent;
	rec->dropped   += ctx->drops;

	/* Record bulk events, then userspace can calc average bulk size */
	rec->info += 1;

	/* Record error cases, where no frame were sent */
	if (ctx->err)
		rec->err++;

	/* Catch API error of drv ndo_xdp_xmit sent more than count */
	if (ctx->drops < 0)
		rec->err++;

	return 1;
}