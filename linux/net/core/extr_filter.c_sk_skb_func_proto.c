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
#define  BPF_FUNC_get_socket_cookie 141 
#define  BPF_FUNC_get_socket_uid 140 
#define  BPF_FUNC_perf_event_output 139 
#define  BPF_FUNC_sk_lookup_tcp 138 
#define  BPF_FUNC_sk_lookup_udp 137 
#define  BPF_FUNC_sk_redirect_hash 136 
#define  BPF_FUNC_sk_redirect_map 135 
#define  BPF_FUNC_sk_release 134 
#define  BPF_FUNC_skb_change_head 133 
#define  BPF_FUNC_skb_change_tail 132 
#define  BPF_FUNC_skb_load_bytes 131 
#define  BPF_FUNC_skb_pull_data 130 
#define  BPF_FUNC_skb_store_bytes 129 
#define  BPF_FUNC_skc_lookup_tcp 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_get_socket_cookie_proto ; 
 struct bpf_func_proto const bpf_get_socket_uid_proto ; 
 struct bpf_func_proto const bpf_sk_lookup_tcp_proto ; 
 struct bpf_func_proto const bpf_sk_lookup_udp_proto ; 
 struct bpf_func_proto const bpf_sk_redirect_hash_proto ; 
 struct bpf_func_proto const bpf_sk_redirect_map_proto ; 
 struct bpf_func_proto const bpf_sk_release_proto ; 
 struct bpf_func_proto const bpf_skb_event_output_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_store_bytes_proto ; 
 struct bpf_func_proto const bpf_skc_lookup_tcp_proto ; 
 struct bpf_func_proto const sk_skb_change_head_proto ; 
 struct bpf_func_proto const sk_skb_change_tail_proto ; 
 struct bpf_func_proto const sk_skb_pull_data_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
sk_skb_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_skb_store_bytes:
		return &bpf_skb_store_bytes_proto;
	case BPF_FUNC_skb_load_bytes:
		return &bpf_skb_load_bytes_proto;
	case BPF_FUNC_skb_pull_data:
		return &sk_skb_pull_data_proto;
	case BPF_FUNC_skb_change_tail:
		return &sk_skb_change_tail_proto;
	case BPF_FUNC_skb_change_head:
		return &sk_skb_change_head_proto;
	case BPF_FUNC_get_socket_cookie:
		return &bpf_get_socket_cookie_proto;
	case BPF_FUNC_get_socket_uid:
		return &bpf_get_socket_uid_proto;
	case BPF_FUNC_sk_redirect_map:
		return &bpf_sk_redirect_map_proto;
	case BPF_FUNC_sk_redirect_hash:
		return &bpf_sk_redirect_hash_proto;
	case BPF_FUNC_perf_event_output:
		return &bpf_skb_event_output_proto;
#ifdef CONFIG_INET
	case BPF_FUNC_sk_lookup_tcp:
		return &bpf_sk_lookup_tcp_proto;
	case BPF_FUNC_sk_lookup_udp:
		return &bpf_sk_lookup_udp_proto;
	case BPF_FUNC_sk_release:
		return &bpf_sk_release_proto;
	case BPF_FUNC_skc_lookup_tcp:
		return &bpf_skc_lookup_tcp_proto;
#endif
	default:
		return bpf_base_func_proto(func_id);
	}
}