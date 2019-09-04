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
struct bpf_prog {int dummy; } ;
struct bpf_func_proto {int dummy; } ;
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
#define  BPF_FUNC_csum_diff 136 
#define  BPF_FUNC_fib_lookup 135 
#define  BPF_FUNC_get_smp_processor_id 134 
#define  BPF_FUNC_perf_event_output 133 
#define  BPF_FUNC_redirect 132 
#define  BPF_FUNC_redirect_map 131 
#define  BPF_FUNC_xdp_adjust_head 130 
#define  BPF_FUNC_xdp_adjust_meta 129 
#define  BPF_FUNC_xdp_adjust_tail 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_csum_diff_proto ; 
 struct bpf_func_proto const bpf_get_smp_processor_id_proto ; 
 struct bpf_func_proto const bpf_xdp_adjust_head_proto ; 
 struct bpf_func_proto const bpf_xdp_adjust_meta_proto ; 
 struct bpf_func_proto const bpf_xdp_adjust_tail_proto ; 
 struct bpf_func_proto const bpf_xdp_event_output_proto ; 
 struct bpf_func_proto const bpf_xdp_fib_lookup_proto ; 
 struct bpf_func_proto const bpf_xdp_redirect_map_proto ; 
 struct bpf_func_proto const bpf_xdp_redirect_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
xdp_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_perf_event_output:
		return &bpf_xdp_event_output_proto;
	case BPF_FUNC_get_smp_processor_id:
		return &bpf_get_smp_processor_id_proto;
	case BPF_FUNC_csum_diff:
		return &bpf_csum_diff_proto;
	case BPF_FUNC_xdp_adjust_head:
		return &bpf_xdp_adjust_head_proto;
	case BPF_FUNC_xdp_adjust_meta:
		return &bpf_xdp_adjust_meta_proto;
	case BPF_FUNC_redirect:
		return &bpf_xdp_redirect_proto;
	case BPF_FUNC_redirect_map:
		return &bpf_xdp_redirect_map_proto;
	case BPF_FUNC_xdp_adjust_tail:
		return &bpf_xdp_adjust_tail_proto;
	case BPF_FUNC_fib_lookup:
		return &bpf_xdp_fib_lookup_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}