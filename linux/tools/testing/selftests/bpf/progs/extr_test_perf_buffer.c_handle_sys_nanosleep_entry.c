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
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  cpu ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_CURRENT_CPU ; 
 int bpf_get_smp_processor_id () ; 
 int /*<<< orphan*/  bpf_perf_event_output (struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  perf_buf_map ; 

int handle_sys_nanosleep_entry(struct pt_regs *ctx)
{
	int cpu = bpf_get_smp_processor_id();

	bpf_perf_event_output(ctx, &perf_buf_map, BPF_F_CURRENT_CPU,
			      &cpu, sizeof(cpu));
	return 0;
}