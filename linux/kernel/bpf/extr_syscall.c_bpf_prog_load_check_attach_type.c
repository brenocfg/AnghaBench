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
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
#define  BPF_CGROUP_GETSOCKOPT 146 
#define  BPF_CGROUP_INET4_BIND 145 
#define  BPF_CGROUP_INET4_CONNECT 144 
#define  BPF_CGROUP_INET4_POST_BIND 143 
#define  BPF_CGROUP_INET6_BIND 142 
#define  BPF_CGROUP_INET6_CONNECT 141 
#define  BPF_CGROUP_INET6_POST_BIND 140 
#define  BPF_CGROUP_INET_EGRESS 139 
#define  BPF_CGROUP_INET_INGRESS 138 
#define  BPF_CGROUP_INET_SOCK_CREATE 137 
#define  BPF_CGROUP_SETSOCKOPT 136 
#define  BPF_CGROUP_UDP4_RECVMSG 135 
#define  BPF_CGROUP_UDP4_SENDMSG 134 
#define  BPF_CGROUP_UDP6_RECVMSG 133 
#define  BPF_CGROUP_UDP6_SENDMSG 132 
#define  BPF_PROG_TYPE_CGROUP_SKB 131 
#define  BPF_PROG_TYPE_CGROUP_SOCK 130 
#define  BPF_PROG_TYPE_CGROUP_SOCKOPT 129 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 128 
 int EINVAL ; 

__attribute__((used)) static int
bpf_prog_load_check_attach_type(enum bpf_prog_type prog_type,
				enum bpf_attach_type expected_attach_type)
{
	switch (prog_type) {
	case BPF_PROG_TYPE_CGROUP_SOCK:
		switch (expected_attach_type) {
		case BPF_CGROUP_INET_SOCK_CREATE:
		case BPF_CGROUP_INET4_POST_BIND:
		case BPF_CGROUP_INET6_POST_BIND:
			return 0;
		default:
			return -EINVAL;
		}
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		switch (expected_attach_type) {
		case BPF_CGROUP_INET4_BIND:
		case BPF_CGROUP_INET6_BIND:
		case BPF_CGROUP_INET4_CONNECT:
		case BPF_CGROUP_INET6_CONNECT:
		case BPF_CGROUP_UDP4_SENDMSG:
		case BPF_CGROUP_UDP6_SENDMSG:
		case BPF_CGROUP_UDP4_RECVMSG:
		case BPF_CGROUP_UDP6_RECVMSG:
			return 0;
		default:
			return -EINVAL;
		}
	case BPF_PROG_TYPE_CGROUP_SKB:
		switch (expected_attach_type) {
		case BPF_CGROUP_INET_INGRESS:
		case BPF_CGROUP_INET_EGRESS:
			return 0;
		default:
			return -EINVAL;
		}
	case BPF_PROG_TYPE_CGROUP_SOCKOPT:
		switch (expected_attach_type) {
		case BPF_CGROUP_SETSOCKOPT:
		case BPF_CGROUP_GETSOCKOPT:
			return 0;
		default:
			return -EINVAL;
		}
	default:
		return 0;
	}
}