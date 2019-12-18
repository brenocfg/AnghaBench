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
struct random_urandom_args {int dummy; } ;
struct bpf_stack_build_id {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int BPF_F_USER_BUILD_ID ; 
 int BPF_F_USER_STACK ; 
 int PERF_MAX_STACK_DEPTH ; 
 int /*<<< orphan*/  bpf_get_stack (struct random_urandom_args*,void*,int,int) ; 
 int bpf_get_stackid (struct random_urandom_args*,int /*<<< orphan*/ *,int) ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_map ; 
 int /*<<< orphan*/  stack_amap ; 
 int /*<<< orphan*/  stackid_hmap ; 
 int /*<<< orphan*/  stackmap ; 

int oncpu(struct random_urandom_args *args)
{
	__u32 max_len = sizeof(struct bpf_stack_build_id)
			* PERF_MAX_STACK_DEPTH;
	__u32 key = 0, val = 0, *value_p;
	void *stack_p;

	value_p = bpf_map_lookup_elem(&control_map, &key);
	if (value_p && *value_p)
		return 0; /* skip if non-zero *value_p */

	/* The size of stackmap and stackid_hmap should be the same */
	key = bpf_get_stackid(args, &stackmap, BPF_F_USER_STACK);
	if ((int)key >= 0) {
		bpf_map_update_elem(&stackid_hmap, &key, &val, 0);
		stack_p = bpf_map_lookup_elem(&stack_amap, &key);
		if (stack_p)
			bpf_get_stack(args, stack_p, max_len,
				      BPF_F_USER_STACK | BPF_F_USER_BUILD_ID);
	}

	return 0;
}