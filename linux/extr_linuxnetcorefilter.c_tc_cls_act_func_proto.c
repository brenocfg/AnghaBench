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
#define  BPF_FUNC_clone_redirect 158 
#define  BPF_FUNC_csum_diff 157 
#define  BPF_FUNC_csum_update 156 
#define  BPF_FUNC_fib_lookup 155 
#define  BPF_FUNC_get_cgroup_classid 154 
#define  BPF_FUNC_get_hash_recalc 153 
#define  BPF_FUNC_get_route_realm 152 
#define  BPF_FUNC_get_smp_processor_id 151 
#define  BPF_FUNC_get_socket_cookie 150 
#define  BPF_FUNC_get_socket_uid 149 
#define  BPF_FUNC_l3_csum_replace 148 
#define  BPF_FUNC_l4_csum_replace 147 
#define  BPF_FUNC_perf_event_output 146 
#define  BPF_FUNC_redirect 145 
#define  BPF_FUNC_set_hash 144 
#define  BPF_FUNC_set_hash_invalid 143 
#define  BPF_FUNC_skb_adjust_room 142 
#define  BPF_FUNC_skb_change_proto 141 
#define  BPF_FUNC_skb_change_tail 140 
#define  BPF_FUNC_skb_change_type 139 
#define  BPF_FUNC_skb_get_tunnel_key 138 
#define  BPF_FUNC_skb_get_tunnel_opt 137 
#define  BPF_FUNC_skb_load_bytes 136 
#define  BPF_FUNC_skb_load_bytes_relative 135 
#define  BPF_FUNC_skb_pull_data 134 
#define  BPF_FUNC_skb_set_tunnel_key 133 
#define  BPF_FUNC_skb_set_tunnel_opt 132 
#define  BPF_FUNC_skb_store_bytes 131 
#define  BPF_FUNC_skb_under_cgroup 130 
#define  BPF_FUNC_skb_vlan_pop 129 
#define  BPF_FUNC_skb_vlan_push 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_clone_redirect_proto ; 
 struct bpf_func_proto const bpf_csum_diff_proto ; 
 struct bpf_func_proto const bpf_csum_update_proto ; 
 struct bpf_func_proto const bpf_get_cgroup_classid_proto ; 
 struct bpf_func_proto const bpf_get_hash_recalc_proto ; 
 struct bpf_func_proto const bpf_get_route_realm_proto ; 
 struct bpf_func_proto const* bpf_get_skb_set_tunnel_proto (int) ; 
 struct bpf_func_proto const bpf_get_smp_processor_id_proto ; 
 struct bpf_func_proto const bpf_get_socket_cookie_proto ; 
 struct bpf_func_proto const bpf_get_socket_uid_proto ; 
 struct bpf_func_proto const bpf_l3_csum_replace_proto ; 
 struct bpf_func_proto const bpf_l4_csum_replace_proto ; 
 struct bpf_func_proto const bpf_redirect_proto ; 
 struct bpf_func_proto const bpf_set_hash_invalid_proto ; 
 struct bpf_func_proto const bpf_set_hash_proto ; 
 struct bpf_func_proto const bpf_skb_adjust_room_proto ; 
 struct bpf_func_proto const bpf_skb_change_proto_proto ; 
 struct bpf_func_proto const bpf_skb_change_tail_proto ; 
 struct bpf_func_proto const bpf_skb_change_type_proto ; 
 struct bpf_func_proto const bpf_skb_event_output_proto ; 
 struct bpf_func_proto const bpf_skb_fib_lookup_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_key_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_opt_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_relative_proto ; 
 struct bpf_func_proto const bpf_skb_pull_data_proto ; 
 struct bpf_func_proto const bpf_skb_store_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_under_cgroup_proto ; 
 struct bpf_func_proto const bpf_skb_vlan_pop_proto ; 
 struct bpf_func_proto const bpf_skb_vlan_push_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
tc_cls_act_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_skb_store_bytes:
		return &bpf_skb_store_bytes_proto;
	case BPF_FUNC_skb_load_bytes:
		return &bpf_skb_load_bytes_proto;
	case BPF_FUNC_skb_load_bytes_relative:
		return &bpf_skb_load_bytes_relative_proto;
	case BPF_FUNC_skb_pull_data:
		return &bpf_skb_pull_data_proto;
	case BPF_FUNC_csum_diff:
		return &bpf_csum_diff_proto;
	case BPF_FUNC_csum_update:
		return &bpf_csum_update_proto;
	case BPF_FUNC_l3_csum_replace:
		return &bpf_l3_csum_replace_proto;
	case BPF_FUNC_l4_csum_replace:
		return &bpf_l4_csum_replace_proto;
	case BPF_FUNC_clone_redirect:
		return &bpf_clone_redirect_proto;
	case BPF_FUNC_get_cgroup_classid:
		return &bpf_get_cgroup_classid_proto;
	case BPF_FUNC_skb_vlan_push:
		return &bpf_skb_vlan_push_proto;
	case BPF_FUNC_skb_vlan_pop:
		return &bpf_skb_vlan_pop_proto;
	case BPF_FUNC_skb_change_proto:
		return &bpf_skb_change_proto_proto;
	case BPF_FUNC_skb_change_type:
		return &bpf_skb_change_type_proto;
	case BPF_FUNC_skb_adjust_room:
		return &bpf_skb_adjust_room_proto;
	case BPF_FUNC_skb_change_tail:
		return &bpf_skb_change_tail_proto;
	case BPF_FUNC_skb_get_tunnel_key:
		return &bpf_skb_get_tunnel_key_proto;
	case BPF_FUNC_skb_set_tunnel_key:
		return bpf_get_skb_set_tunnel_proto(func_id);
	case BPF_FUNC_skb_get_tunnel_opt:
		return &bpf_skb_get_tunnel_opt_proto;
	case BPF_FUNC_skb_set_tunnel_opt:
		return bpf_get_skb_set_tunnel_proto(func_id);
	case BPF_FUNC_redirect:
		return &bpf_redirect_proto;
	case BPF_FUNC_get_route_realm:
		return &bpf_get_route_realm_proto;
	case BPF_FUNC_get_hash_recalc:
		return &bpf_get_hash_recalc_proto;
	case BPF_FUNC_set_hash_invalid:
		return &bpf_set_hash_invalid_proto;
	case BPF_FUNC_set_hash:
		return &bpf_set_hash_proto;
	case BPF_FUNC_perf_event_output:
		return &bpf_skb_event_output_proto;
	case BPF_FUNC_get_smp_processor_id:
		return &bpf_get_smp_processor_id_proto;
	case BPF_FUNC_skb_under_cgroup:
		return &bpf_skb_under_cgroup_proto;
	case BPF_FUNC_get_socket_cookie:
		return &bpf_get_socket_cookie_proto;
	case BPF_FUNC_get_socket_uid:
		return &bpf_get_socket_uid_proto;
	case BPF_FUNC_fib_lookup:
		return &bpf_skb_fib_lookup_proto;
#ifdef CONFIG_XFRM
	case BPF_FUNC_skb_get_xfrm_state:
		return &bpf_skb_get_xfrm_state_proto;
#endif
#ifdef CONFIG_SOCK_CGROUP_DATA
	case BPF_FUNC_skb_cgroup_id:
		return &bpf_skb_cgroup_id_proto;
	case BPF_FUNC_skb_ancestor_cgroup_id:
		return &bpf_skb_ancestor_cgroup_id_proto;
#endif
	default:
		return bpf_base_func_proto(func_id);
	}
}