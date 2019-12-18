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
#define  BPF_FUNC_msg_apply_bytes 134 
#define  BPF_FUNC_msg_cork_bytes 133 
#define  BPF_FUNC_msg_pop_data 132 
#define  BPF_FUNC_msg_pull_data 131 
#define  BPF_FUNC_msg_push_data 130 
#define  BPF_FUNC_msg_redirect_hash 129 
#define  BPF_FUNC_msg_redirect_map 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_msg_apply_bytes_proto ; 
 struct bpf_func_proto const bpf_msg_cork_bytes_proto ; 
 struct bpf_func_proto const bpf_msg_pop_data_proto ; 
 struct bpf_func_proto const bpf_msg_pull_data_proto ; 
 struct bpf_func_proto const bpf_msg_push_data_proto ; 
 struct bpf_func_proto const bpf_msg_redirect_hash_proto ; 
 struct bpf_func_proto const bpf_msg_redirect_map_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
sk_msg_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_msg_redirect_map:
		return &bpf_msg_redirect_map_proto;
	case BPF_FUNC_msg_redirect_hash:
		return &bpf_msg_redirect_hash_proto;
	case BPF_FUNC_msg_apply_bytes:
		return &bpf_msg_apply_bytes_proto;
	case BPF_FUNC_msg_cork_bytes:
		return &bpf_msg_cork_bytes_proto;
	case BPF_FUNC_msg_pull_data:
		return &bpf_msg_pull_data_proto;
	case BPF_FUNC_msg_push_data:
		return &bpf_msg_push_data_proto;
	case BPF_FUNC_msg_pop_data:
		return &bpf_msg_pop_data_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}