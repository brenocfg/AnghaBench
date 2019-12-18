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
#define  BPF_FUNC_get_local_storage 138 
#define  BPF_FUNC_get_socket_cookie 137 
#define  BPF_FUNC_getsockopt 136 
#define  BPF_FUNC_perf_event_output 135 
#define  BPF_FUNC_setsockopt 134 
#define  BPF_FUNC_sk_storage_delete 133 
#define  BPF_FUNC_sk_storage_get 132 
#define  BPF_FUNC_sock_hash_update 131 
#define  BPF_FUNC_sock_map_update 130 
#define  BPF_FUNC_sock_ops_cb_flags_set 129 
#define  BPF_FUNC_tcp_sock 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const bpf_get_socket_cookie_sock_ops_proto ; 
 struct bpf_func_proto const bpf_getsockopt_proto ; 
 struct bpf_func_proto const bpf_setsockopt_proto ; 
 struct bpf_func_proto const bpf_sk_storage_delete_proto ; 
 struct bpf_func_proto const bpf_sk_storage_get_proto ; 
 struct bpf_func_proto const bpf_sock_hash_update_proto ; 
 struct bpf_func_proto const bpf_sock_map_update_proto ; 
 struct bpf_func_proto const bpf_sock_ops_cb_flags_set_proto ; 
 struct bpf_func_proto const bpf_sockopt_event_output_proto ; 
 struct bpf_func_proto const bpf_tcp_sock_proto ; 

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
	case BPF_FUNC_perf_event_output:
		return &bpf_sockopt_event_output_proto;
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
#ifdef CONFIG_INET
	case BPF_FUNC_tcp_sock:
		return &bpf_tcp_sock_proto;
#endif /* CONFIG_INET */
	default:
		return bpf_base_func_proto(func_id);
	}
}