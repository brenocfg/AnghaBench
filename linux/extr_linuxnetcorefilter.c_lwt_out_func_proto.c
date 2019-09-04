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
#define  BPF_FUNC_get_cgroup_classid 135 
#define  BPF_FUNC_get_hash_recalc 134 
#define  BPF_FUNC_get_route_realm 133 
#define  BPF_FUNC_get_smp_processor_id 132 
#define  BPF_FUNC_perf_event_output 131 
#define  BPF_FUNC_skb_load_bytes 130 
#define  BPF_FUNC_skb_pull_data 129 
#define  BPF_FUNC_skb_under_cgroup 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_csum_diff_proto ; 
 struct bpf_func_proto const bpf_get_cgroup_classid_proto ; 
 struct bpf_func_proto const bpf_get_hash_recalc_proto ; 
 struct bpf_func_proto const bpf_get_route_realm_proto ; 
 struct bpf_func_proto const bpf_get_smp_processor_id_proto ; 
 struct bpf_func_proto const bpf_skb_event_output_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_pull_data_proto ; 
 struct bpf_func_proto const bpf_skb_under_cgroup_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
lwt_out_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_skb_load_bytes:
		return &bpf_skb_load_bytes_proto;
	case BPF_FUNC_skb_pull_data:
		return &bpf_skb_pull_data_proto;
	case BPF_FUNC_csum_diff:
		return &bpf_csum_diff_proto;
	case BPF_FUNC_get_cgroup_classid:
		return &bpf_get_cgroup_classid_proto;
	case BPF_FUNC_get_route_realm:
		return &bpf_get_route_realm_proto;
	case BPF_FUNC_get_hash_recalc:
		return &bpf_get_hash_recalc_proto;
	case BPF_FUNC_perf_event_output:
		return &bpf_skb_event_output_proto;
	case BPF_FUNC_get_smp_processor_id:
		return &bpf_get_smp_processor_id_proto;
	case BPF_FUNC_skb_under_cgroup:
		return &bpf_skb_under_cgroup_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}