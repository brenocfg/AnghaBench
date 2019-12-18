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
#define  BPF_FUNC_get_listener_sock 136 
#define  BPF_FUNC_get_local_storage 135 
#define  BPF_FUNC_perf_event_output 134 
#define  BPF_FUNC_sk_fullsock 133 
#define  BPF_FUNC_sk_storage_delete 132 
#define  BPF_FUNC_sk_storage_get 131 
#define  BPF_FUNC_skb_cgroup_id 130 
#define  BPF_FUNC_skb_ecn_set_ce 129 
#define  BPF_FUNC_tcp_sock 128 
 struct bpf_func_proto const bpf_get_listener_sock_proto ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const bpf_sk_fullsock_proto ; 
 struct bpf_func_proto const bpf_sk_storage_delete_proto ; 
 struct bpf_func_proto const bpf_sk_storage_get_proto ; 
 struct bpf_func_proto const bpf_skb_cgroup_id_proto ; 
 struct bpf_func_proto const bpf_skb_ecn_set_ce_proto ; 
 struct bpf_func_proto const bpf_skb_event_output_proto ; 
 struct bpf_func_proto const bpf_tcp_sock_proto ; 
 struct bpf_func_proto const* sk_filter_func_proto (int,struct bpf_prog const*) ; 

__attribute__((used)) static const struct bpf_func_proto *
cg_skb_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_get_local_storage:
		return &bpf_get_local_storage_proto;
	case BPF_FUNC_sk_fullsock:
		return &bpf_sk_fullsock_proto;
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
	case BPF_FUNC_perf_event_output:
		return &bpf_skb_event_output_proto;
#ifdef CONFIG_SOCK_CGROUP_DATA
	case BPF_FUNC_skb_cgroup_id:
		return &bpf_skb_cgroup_id_proto;
#endif
#ifdef CONFIG_INET
	case BPF_FUNC_tcp_sock:
		return &bpf_tcp_sock_proto;
	case BPF_FUNC_get_listener_sock:
		return &bpf_get_listener_sock_proto;
	case BPF_FUNC_skb_ecn_set_ce:
		return &bpf_skb_ecn_set_ce_proto;
#endif
	default:
		return sk_filter_func_proto(func_id, prog);
	}
}