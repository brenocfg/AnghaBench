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
#define  BPF_FUNC_sk_storage_delete 130 
#define  BPF_FUNC_sk_storage_get 129 
#define  BPF_FUNC_tcp_sock 128 
 struct bpf_func_proto const bpf_sk_storage_delete_proto ; 
 struct bpf_func_proto const bpf_sk_storage_get_proto ; 
 struct bpf_func_proto const bpf_tcp_sock_proto ; 
 struct bpf_func_proto const* cgroup_base_func_proto (int,struct bpf_prog const*) ; 

__attribute__((used)) static const struct bpf_func_proto *
cg_sockopt_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
#ifdef CONFIG_NET
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
#endif
#ifdef CONFIG_INET
	case BPF_FUNC_tcp_sock:
		return &bpf_tcp_sock_proto;
#endif
	default:
		return cgroup_base_func_proto(func_id, prog);
	}
}