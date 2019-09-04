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
struct bpf_func_proto {int dummy; } ;
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
#define  BPF_FUNC_get_numa_node_id 136 
#define  BPF_FUNC_get_prandom_u32 135 
#define  BPF_FUNC_get_smp_processor_id 134 
#define  BPF_FUNC_ktime_get_ns 133 
#define  BPF_FUNC_map_delete_elem 132 
#define  BPF_FUNC_map_lookup_elem 131 
#define  BPF_FUNC_map_update_elem 130 
#define  BPF_FUNC_tail_call 129 
#define  BPF_FUNC_trace_printk 128 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 struct bpf_func_proto const bpf_get_numa_node_id_proto ; 
 struct bpf_func_proto const bpf_get_prandom_u32_proto ; 
 struct bpf_func_proto const bpf_get_raw_smp_processor_id_proto ; 
 struct bpf_func_proto const* bpf_get_trace_printk_proto () ; 
 struct bpf_func_proto const bpf_ktime_get_ns_proto ; 
 struct bpf_func_proto const bpf_map_delete_elem_proto ; 
 struct bpf_func_proto const bpf_map_lookup_elem_proto ; 
 struct bpf_func_proto const bpf_map_update_elem_proto ; 
 struct bpf_func_proto const bpf_tail_call_proto ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct bpf_func_proto *
bpf_base_func_proto(enum bpf_func_id func_id)
{
	switch (func_id) {
	case BPF_FUNC_map_lookup_elem:
		return &bpf_map_lookup_elem_proto;
	case BPF_FUNC_map_update_elem:
		return &bpf_map_update_elem_proto;
	case BPF_FUNC_map_delete_elem:
		return &bpf_map_delete_elem_proto;
	case BPF_FUNC_get_prandom_u32:
		return &bpf_get_prandom_u32_proto;
	case BPF_FUNC_get_smp_processor_id:
		return &bpf_get_raw_smp_processor_id_proto;
	case BPF_FUNC_get_numa_node_id:
		return &bpf_get_numa_node_id_proto;
	case BPF_FUNC_tail_call:
		return &bpf_tail_call_proto;
	case BPF_FUNC_ktime_get_ns:
		return &bpf_ktime_get_ns_proto;
	case BPF_FUNC_trace_printk:
		if (capable(CAP_SYS_ADMIN))
			return bpf_get_trace_printk_proto();
		/* else: fall through */
	default:
		return NULL;
	}
}