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
struct sched_switch_args {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int PERF_MAX_STACK_DEPTH ; 
 int /*<<< orphan*/  bpf_get_stack (struct sched_switch_args*,void*,int,int /*<<< orphan*/ ) ; 
 int bpf_get_stackid (struct sched_switch_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_map ; 
 int /*<<< orphan*/  stack_amap ; 
 int /*<<< orphan*/  stackid_hmap ; 
 int /*<<< orphan*/  stackmap ; 

int oncpu(struct sched_switch_args *ctx)
{
	__u32 max_len = PERF_MAX_STACK_DEPTH * sizeof(__u64);
	__u32 key = 0, val = 0, *value_p;
	void *stack_p;

	value_p = bpf_map_lookup_elem(&control_map, &key);
	if (value_p && *value_p)
		return 0; /* skip if non-zero *value_p */

	/* The size of stackmap and stackid_hmap should be the same */
	key = bpf_get_stackid(ctx, &stackmap, 0);
	if ((int)key >= 0) {
		bpf_map_update_elem(&stackid_hmap, &key, &val, 0);
		stack_p = bpf_map_lookup_elem(&stack_amap, &key);
		if (stack_p)
			bpf_get_stack(ctx, stack_p, max_len, 0);
	}

	return 0;
}