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
typedef  scalar_t__ u32 ;
struct datarec {int issue; int /*<<< orphan*/  dropped; int /*<<< orphan*/  processed; } ;
struct cpumap_enqueue_ctx {scalar_t__ to_cpu; scalar_t__ processed; scalar_t__ drops; } ;

/* Variables and functions */
 scalar_t__ MAX_CPUS ; 
 struct datarec* bpf_map_lookup_elem (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  cpumap_enqueue_cnt ; 

int trace_xdp_cpumap_enqueue(struct cpumap_enqueue_ctx *ctx)
{
	u32 to_cpu = ctx->to_cpu;
	struct datarec *rec;

	if (to_cpu >= MAX_CPUS)
		return 1;

	rec = bpf_map_lookup_elem(&cpumap_enqueue_cnt, &to_cpu);
	if (!rec)
		return 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;

	/* Record bulk events, then userspace can calc average bulk size */
	if (ctx->processed > 0)
		rec->issue += 1;

	/* Inception: It's possible to detect overload situations, via
	 * this tracepoint.  This can be used for creating a feedback
	 * loop to XDP, which can take appropriate actions to mitigate
	 * this overload situation.
	 */
	return 0;
}