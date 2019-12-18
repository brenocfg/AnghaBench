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
#define  BPF_FUNC_clone_redirect 173 
#define  BPF_FUNC_csum_diff 172 
#define  BPF_FUNC_csum_update 171 
#define  BPF_FUNC_fib_lookup 170 
#define  BPF_FUNC_get_cgroup_classid 169 
#define  BPF_FUNC_get_hash_recalc 168 
#define  BPF_FUNC_get_listener_sock 167 
#define  BPF_FUNC_get_route_realm 166 
#define  BPF_FUNC_get_smp_processor_id 165 
#define  BPF_FUNC_get_socket_cookie 164 
#define  BPF_FUNC_get_socket_uid 163 
#define  BPF_FUNC_l3_csum_replace 162 
#define  BPF_FUNC_l4_csum_replace 161 
#define  BPF_FUNC_perf_event_output 160 
#define  BPF_FUNC_redirect 159 
#define  BPF_FUNC_set_hash 158 
#define  BPF_FUNC_set_hash_invalid 157 
#define  BPF_FUNC_sk_fullsock 156 
#define  BPF_FUNC_sk_lookup_tcp 155 
#define  BPF_FUNC_sk_lookup_udp 154 
#define  BPF_FUNC_sk_release 153 
#define  BPF_FUNC_sk_storage_delete 152 
#define  BPF_FUNC_sk_storage_get 151 
#define  BPF_FUNC_skb_adjust_room 150 
#define  BPF_FUNC_skb_ancestor_cgroup_id 149 
#define  BPF_FUNC_skb_cgroup_id 148 
#define  BPF_FUNC_skb_change_proto 147 
#define  BPF_FUNC_skb_change_tail 146 
#define  BPF_FUNC_skb_change_type 145 
#define  BPF_FUNC_skb_ecn_set_ce 144 
#define  BPF_FUNC_skb_get_tunnel_key 143 
#define  BPF_FUNC_skb_get_tunnel_opt 142 
#define  BPF_FUNC_skb_get_xfrm_state 141 
#define  BPF_FUNC_skb_load_bytes 140 
#define  BPF_FUNC_skb_load_bytes_relative 139 
#define  BPF_FUNC_skb_pull_data 138 
#define  BPF_FUNC_skb_set_tunnel_key 137 
#define  BPF_FUNC_skb_set_tunnel_opt 136 
#define  BPF_FUNC_skb_store_bytes 135 
#define  BPF_FUNC_skb_under_cgroup 134 
#define  BPF_FUNC_skb_vlan_pop 133 
#define  BPF_FUNC_skb_vlan_push 132 
#define  BPF_FUNC_skc_lookup_tcp 131 
#define  BPF_FUNC_tcp_check_syncookie 130 
#define  BPF_FUNC_tcp_gen_syncookie 129 
#define  BPF_FUNC_tcp_sock 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_clone_redirect_proto ; 
 struct bpf_func_proto const bpf_csum_diff_proto ; 
 struct bpf_func_proto const bpf_csum_update_proto ; 
 struct bpf_func_proto const bpf_get_cgroup_classid_proto ; 
 struct bpf_func_proto const bpf_get_hash_recalc_proto ; 
 struct bpf_func_proto const bpf_get_listener_sock_proto ; 
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
 struct bpf_func_proto const bpf_sk_fullsock_proto ; 
 struct bpf_func_proto const bpf_sk_lookup_tcp_proto ; 
 struct bpf_func_proto const bpf_sk_lookup_udp_proto ; 
 struct bpf_func_proto const bpf_sk_release_proto ; 
 struct bpf_func_proto const bpf_sk_storage_delete_proto ; 
 struct bpf_func_proto const bpf_sk_storage_get_proto ; 
 struct bpf_func_proto const bpf_skb_adjust_room_proto ; 
 struct bpf_func_proto const bpf_skb_ancestor_cgroup_id_proto ; 
 struct bpf_func_proto const bpf_skb_cgroup_id_proto ; 
 struct bpf_func_proto const bpf_skb_change_proto_proto ; 
 struct bpf_func_proto const bpf_skb_change_tail_proto ; 
 struct bpf_func_proto const bpf_skb_change_type_proto ; 
 struct bpf_func_proto const bpf_skb_ecn_set_ce_proto ; 
 struct bpf_func_proto const bpf_skb_event_output_proto ; 
 struct bpf_func_proto const bpf_skb_fib_lookup_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_key_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_opt_proto ; 
 struct bpf_func_proto const bpf_skb_get_xfrm_state_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_relative_proto ; 
 struct bpf_func_proto const bpf_skb_pull_data_proto ; 
 struct bpf_func_proto const bpf_skb_store_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_under_cgroup_proto ; 
 struct bpf_func_proto const bpf_skb_vlan_pop_proto ; 
 struct bpf_func_proto const bpf_skb_vlan_push_proto ; 
 struct bpf_func_proto const bpf_skc_lookup_tcp_proto ; 
 struct bpf_func_proto const bpf_tcp_check_syncookie_proto ; 
 struct bpf_func_proto const bpf_tcp_gen_syncookie_proto ; 
 struct bpf_func_proto const bpf_tcp_sock_proto ; 

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
	case BPF_FUNC_sk_fullsock:
		return &bpf_sk_fullsock_proto;
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
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
#ifdef CONFIG_INET
	case BPF_FUNC_sk_lookup_tcp:
		return &bpf_sk_lookup_tcp_proto;
	case BPF_FUNC_sk_lookup_udp:
		return &bpf_sk_lookup_udp_proto;
	case BPF_FUNC_sk_release:
		return &bpf_sk_release_proto;
	case BPF_FUNC_tcp_sock:
		return &bpf_tcp_sock_proto;
	case BPF_FUNC_get_listener_sock:
		return &bpf_get_listener_sock_proto;
	case BPF_FUNC_skc_lookup_tcp:
		return &bpf_skc_lookup_tcp_proto;
	case BPF_FUNC_tcp_check_syncookie:
		return &bpf_tcp_check_syncookie_proto;
	case BPF_FUNC_skb_ecn_set_ce:
		return &bpf_skb_ecn_set_ce_proto;
	case BPF_FUNC_tcp_gen_syncookie:
		return &bpf_tcp_gen_syncookie_proto;
#endif
	default:
		return bpf_base_func_proto(func_id);
	}
}