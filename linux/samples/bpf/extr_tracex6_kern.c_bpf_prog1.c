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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  bpf_get_smp_processor_id () ; 
 scalar_t__* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_perf_event_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counters ; 
 int /*<<< orphan*/  values ; 

int bpf_prog1(struct pt_regs *ctx)
{
	u32 key = bpf_get_smp_processor_id();
	u64 count, *val;
	s64 error;

	count = bpf_perf_event_read(&counters, key);
	error = (s64)count;
	if (error <= -2 && error >= -22)
		return 0;

	val = bpf_map_lookup_elem(&values, &key);
	if (val)
		*val = count;
	else
		bpf_map_update_elem(&values, &key, &count, BPF_NOEXIST);

	return 0;
}