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
struct bpf_prog {int /*<<< orphan*/  expected_attach_type; } ;
struct bpf_func_proto {int dummy; } ;
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
#define  BPF_CGROUP_INET4_CONNECT 139 
#define  BPF_CGROUP_INET6_CONNECT 138 
#define  BPF_FUNC_bind 137 
#define  BPF_FUNC_get_current_uid_gid 136 
#define  BPF_FUNC_get_local_storage 135 
#define  BPF_FUNC_get_socket_cookie 134 
#define  BPF_FUNC_sk_lookup_tcp 133 
#define  BPF_FUNC_sk_lookup_udp 132 
#define  BPF_FUNC_sk_release 131 
#define  BPF_FUNC_sk_storage_delete 130 
#define  BPF_FUNC_sk_storage_get 129 
#define  BPF_FUNC_skc_lookup_tcp 128 
 struct bpf_func_proto const* bpf_base_func_proto (int) ; 
 struct bpf_func_proto const bpf_bind_proto ; 
 struct bpf_func_proto const bpf_get_current_uid_gid_proto ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const bpf_get_socket_cookie_sock_addr_proto ; 
 struct bpf_func_proto const bpf_sk_release_proto ; 
 struct bpf_func_proto const bpf_sk_storage_delete_proto ; 
 struct bpf_func_proto const bpf_sk_storage_get_proto ; 
 struct bpf_func_proto const bpf_sock_addr_sk_lookup_tcp_proto ; 
 struct bpf_func_proto const bpf_sock_addr_sk_lookup_udp_proto ; 
 struct bpf_func_proto const bpf_sock_addr_skc_lookup_tcp_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
sock_addr_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	/* inet and inet6 sockets are created in a process
	 * context so there is always a valid uid/gid
	 */
	case BPF_FUNC_get_current_uid_gid:
		return &bpf_get_current_uid_gid_proto;
	case BPF_FUNC_bind:
		switch (prog->expected_attach_type) {
		case BPF_CGROUP_INET4_CONNECT:
		case BPF_CGROUP_INET6_CONNECT:
			return &bpf_bind_proto;
		default:
			return NULL;
		}
	case BPF_FUNC_get_socket_cookie:
		return &bpf_get_socket_cookie_sock_addr_proto;
	case BPF_FUNC_get_local_storage:
		return &bpf_get_local_storage_proto;
#ifdef CONFIG_INET
	case BPF_FUNC_sk_lookup_tcp:
		return &bpf_sock_addr_sk_lookup_tcp_proto;
	case BPF_FUNC_sk_lookup_udp:
		return &bpf_sock_addr_sk_lookup_udp_proto;
	case BPF_FUNC_sk_release:
		return &bpf_sk_release_proto;
	case BPF_FUNC_skc_lookup_tcp:
		return &bpf_sock_addr_skc_lookup_tcp_proto;
#endif /* CONFIG_INET */
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
	default:
		return bpf_base_func_proto(func_id);
	}
}