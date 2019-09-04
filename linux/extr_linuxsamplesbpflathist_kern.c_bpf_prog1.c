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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int bpf_get_smp_processor_id () ; 
 int /*<<< orphan*/  bpf_ktime_get_ns () ; 
 int /*<<< orphan*/ * bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  my_map ; 

int bpf_prog1(struct pt_regs *ctx)
{
	int cpu = bpf_get_smp_processor_id();
	u64 *ts = bpf_map_lookup_elem(&my_map, &cpu);

	if (ts)
		*ts = bpf_ktime_get_ns();

	return 0;
}