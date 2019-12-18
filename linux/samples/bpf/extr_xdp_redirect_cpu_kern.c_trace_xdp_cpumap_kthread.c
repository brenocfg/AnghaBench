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
struct datarec {int /*<<< orphan*/  issue; int /*<<< orphan*/  dropped; int /*<<< orphan*/  processed; } ;
struct cpumap_kthread_ctx {scalar_t__ sched; scalar_t__ drops; scalar_t__ processed; } ;

/* Variables and functions */
 struct datarec* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumap_kthread_cnt ; 

int trace_xdp_cpumap_kthread(struct cpumap_kthread_ctx *ctx)
{
	struct datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&cpumap_kthread_cnt, &key);
	if (!rec)
		return 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;

	/* Count times kthread yielded CPU via schedule call */
	if (ctx->sched)
		rec->issue++;

	return 0;
}