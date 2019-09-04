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
#define  BPF_FUNC_get_local_storage 137 
#define  BPF_FUNC_get_socket_cookie 136 
#define  BPF_FUNC_get_socket_uid 135 
#define  BPF_FUNC_sk_redirect_hash 134 
#define  BPF_FUNC_sk_redirect_map 133 
#define  BPF_FUNC_skb_change_head 132 
#define  BPF_FUNC_skb_change_tail 131 
#define  BPF_FUNC_skb_load_bytes 130 
#define  BPF_FUNC_skb_pull_data 129 
#define  BPF_FUNC_skb_store_bytes 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const bpf_get_socket_cookie_proto ; 
 struct bpf_func_proto const bpf_get_socket_uid_proto ; 
 struct bpf_func_proto const bpf_sk_redirect_hash_proto ; 
 struct bpf_func_proto const bpf_sk_redirect_map_proto ; 
 struct bpf_func_proto const bpf_skb_load_bytes_proto ; 
 struct bpf_func_proto const bpf_skb_store_bytes_proto ; 
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
	case BPF_FUNC_get_local_storage:
		return &bpf_get_local_storage_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}