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
#define  BPF_FUNC_get_local_storage 134 
#define  BPF_FUNC_get_socket_cookie 133 
#define  BPF_FUNC_getsockopt 132 
#define  BPF_FUNC_setsockopt 131 
#define  BPF_FUNC_sock_hash_update 130 
#define  BPF_FUNC_sock_map_update 129 
#define  BPF_FUNC_sock_ops_cb_flags_set 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const bpf_get_socket_cookie_sock_ops_proto ; 
 struct bpf_func_proto const bpf_getsockopt_proto ; 
 struct bpf_func_proto const bpf_setsockopt_proto ; 
 struct bpf_func_proto const bpf_sock_hash_update_proto ; 
 struct bpf_func_proto const bpf_sock_map_update_proto ; 
 struct bpf_func_proto const bpf_sock_ops_cb_flags_set_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
sock_ops_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_setsockopt:
		return &bpf_setsockopt_proto;
	case BPF_FUNC_getsockopt:
		return &bpf_getsockopt_proto;
	case BPF_FUNC_sock_ops_cb_flags_set:
		return &bpf_sock_ops_cb_flags_set_proto;
	case BPF_FUNC_sock_map_update:
		return &bpf_sock_map_update_proto;
	case BPF_FUNC_sock_hash_update:
		return &bpf_sock_hash_update_proto;
	case BPF_FUNC_get_socket_cookie:
		return &bpf_get_socket_cookie_sock_ops_proto;
	case BPF_FUNC_get_local_storage:
		return &bpf_get_local_storage_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}