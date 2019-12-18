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
#define  BPF_FUNC_clone_redirect 141 
#define  BPF_FUNC_csum_update 140 
#define  BPF_FUNC_l3_csum_replace 139 
#define  BPF_FUNC_l4_csum_replace 138 
#define  BPF_FUNC_lwt_push_encap 137 
#define  BPF_FUNC_redirect 136 
#define  BPF_FUNC_set_hash_invalid 135 
#define  BPF_FUNC_skb_change_head 134 
#define  BPF_FUNC_skb_change_tail 133 
#define  BPF_FUNC_skb_get_tunnel_key 132 
#define  BPF_FUNC_skb_get_tunnel_opt 131 
#define  BPF_FUNC_skb_set_tunnel_key 130 
#define  BPF_FUNC_skb_set_tunnel_opt 129 
#define  BPF_FUNC_skb_store_bytes 128 
 struct bpf_func_proto const bpf_clone_redirect_proto ; 
 struct bpf_func_proto const bpf_csum_update_proto ; 
 struct bpf_func_proto const* bpf_get_skb_set_tunnel_proto (int) ; 
 struct bpf_func_proto const bpf_l3_csum_replace_proto ; 
 struct bpf_func_proto const bpf_l4_csum_replace_proto ; 
 struct bpf_func_proto const bpf_lwt_xmit_push_encap_proto ; 
 struct bpf_func_proto const bpf_redirect_proto ; 
 struct bpf_func_proto const bpf_set_hash_invalid_proto ; 
 struct bpf_func_proto const bpf_skb_change_head_proto ; 
 struct bpf_func_proto const bpf_skb_change_tail_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_key_proto ; 
 struct bpf_func_proto const bpf_skb_get_tunnel_opt_proto ; 
 struct bpf_func_proto const bpf_skb_store_bytes_proto ; 
 struct bpf_func_proto const* lwt_out_func_proto (int,struct bpf_prog const*) ; 

__attribute__((used)) static const struct bpf_func_proto *
lwt_xmit_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
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
	case BPF_FUNC_clone_redirect:
		return &bpf_clone_redirect_proto;
	case BPF_FUNC_skb_change_tail:
		return &bpf_skb_change_tail_proto;
	case BPF_FUNC_skb_change_head:
		return &bpf_skb_change_head_proto;
	case BPF_FUNC_skb_store_bytes:
		return &bpf_skb_store_bytes_proto;
	case BPF_FUNC_csum_update:
		return &bpf_csum_update_proto;
	case BPF_FUNC_l3_csum_replace:
		return &bpf_l3_csum_replace_proto;
	case BPF_FUNC_l4_csum_replace:
		return &bpf_l4_csum_replace_proto;
	case BPF_FUNC_set_hash_invalid:
		return &bpf_set_hash_invalid_proto;
	case BPF_FUNC_lwt_push_encap:
		return &bpf_lwt_xmit_push_encap_proto;
	default:
		return lwt_out_func_proto(func_id, prog);
	}
}