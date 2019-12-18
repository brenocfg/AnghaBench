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
union bpf_attr {int attach_type; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
#define  BPF_CGROUP_DEVICE 150 
#define  BPF_CGROUP_GETSOCKOPT 149 
#define  BPF_CGROUP_INET4_BIND 148 
#define  BPF_CGROUP_INET4_CONNECT 147 
#define  BPF_CGROUP_INET4_POST_BIND 146 
#define  BPF_CGROUP_INET6_BIND 145 
#define  BPF_CGROUP_INET6_CONNECT 144 
#define  BPF_CGROUP_INET6_POST_BIND 143 
#define  BPF_CGROUP_INET_EGRESS 142 
#define  BPF_CGROUP_INET_INGRESS 141 
#define  BPF_CGROUP_INET_SOCK_CREATE 140 
#define  BPF_CGROUP_SETSOCKOPT 139 
#define  BPF_CGROUP_SOCK_OPS 138 
#define  BPF_CGROUP_SYSCTL 137 
#define  BPF_CGROUP_UDP4_RECVMSG 136 
#define  BPF_CGROUP_UDP4_SENDMSG 135 
#define  BPF_CGROUP_UDP6_RECVMSG 134 
#define  BPF_CGROUP_UDP6_SENDMSG 133 
#define  BPF_FLOW_DISSECTOR 132 
#define  BPF_LIRC_MODE2 131 
 int /*<<< orphan*/  BPF_PROG_DETACH ; 
 int BPF_PROG_TYPE_CGROUP_DEVICE ; 
 int BPF_PROG_TYPE_CGROUP_SKB ; 
 int BPF_PROG_TYPE_CGROUP_SOCK ; 
 int BPF_PROG_TYPE_CGROUP_SOCKOPT ; 
 int BPF_PROG_TYPE_CGROUP_SOCK_ADDR ; 
 int BPF_PROG_TYPE_CGROUP_SYSCTL ; 
 int BPF_PROG_TYPE_SOCK_OPS ; 
#define  BPF_SK_MSG_VERDICT 130 
#define  BPF_SK_SKB_STREAM_PARSER 129 
#define  BPF_SK_SKB_STREAM_VERDICT 128 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int cgroup_bpf_prog_detach (union bpf_attr const*,int) ; 
 int lirc_prog_detach (union bpf_attr const*) ; 
 int skb_flow_dissector_bpf_prog_detach (union bpf_attr const*) ; 
 int sock_map_get_from_fd (union bpf_attr const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_prog_detach(const union bpf_attr *attr)
{
	enum bpf_prog_type ptype;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (CHECK_ATTR(BPF_PROG_DETACH))
		return -EINVAL;

	switch (attr->attach_type) {
	case BPF_CGROUP_INET_INGRESS:
	case BPF_CGROUP_INET_EGRESS:
		ptype = BPF_PROG_TYPE_CGROUP_SKB;
		break;
	case BPF_CGROUP_INET_SOCK_CREATE:
	case BPF_CGROUP_INET4_POST_BIND:
	case BPF_CGROUP_INET6_POST_BIND:
		ptype = BPF_PROG_TYPE_CGROUP_SOCK;
		break;
	case BPF_CGROUP_INET4_BIND:
	case BPF_CGROUP_INET6_BIND:
	case BPF_CGROUP_INET4_CONNECT:
	case BPF_CGROUP_INET6_CONNECT:
	case BPF_CGROUP_UDP4_SENDMSG:
	case BPF_CGROUP_UDP6_SENDMSG:
	case BPF_CGROUP_UDP4_RECVMSG:
	case BPF_CGROUP_UDP6_RECVMSG:
		ptype = BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
		break;
	case BPF_CGROUP_SOCK_OPS:
		ptype = BPF_PROG_TYPE_SOCK_OPS;
		break;
	case BPF_CGROUP_DEVICE:
		ptype = BPF_PROG_TYPE_CGROUP_DEVICE;
		break;
	case BPF_SK_MSG_VERDICT:
		return sock_map_get_from_fd(attr, NULL);
	case BPF_SK_SKB_STREAM_PARSER:
	case BPF_SK_SKB_STREAM_VERDICT:
		return sock_map_get_from_fd(attr, NULL);
	case BPF_LIRC_MODE2:
		return lirc_prog_detach(attr);
	case BPF_FLOW_DISSECTOR:
		return skb_flow_dissector_bpf_prog_detach(attr);
	case BPF_CGROUP_SYSCTL:
		ptype = BPF_PROG_TYPE_CGROUP_SYSCTL;
		break;
	case BPF_CGROUP_GETSOCKOPT:
	case BPF_CGROUP_SETSOCKOPT:
		ptype = BPF_PROG_TYPE_CGROUP_SOCKOPT;
		break;
	default:
		return -EINVAL;
	}

	return cgroup_bpf_prog_detach(attr, ptype);
}