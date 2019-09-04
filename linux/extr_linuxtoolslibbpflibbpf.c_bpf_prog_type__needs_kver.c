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

/* Variables and functions */
#define  BPF_PROG_TYPE_CGROUP_DEVICE 149 
#define  BPF_PROG_TYPE_CGROUP_SKB 148 
#define  BPF_PROG_TYPE_CGROUP_SOCK 147 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 146 
#define  BPF_PROG_TYPE_KPROBE 145 
#define  BPF_PROG_TYPE_LIRC_MODE2 144 
#define  BPF_PROG_TYPE_LWT_IN 143 
#define  BPF_PROG_TYPE_LWT_OUT 142 
#define  BPF_PROG_TYPE_LWT_SEG6LOCAL 141 
#define  BPF_PROG_TYPE_LWT_XMIT 140 
#define  BPF_PROG_TYPE_PERF_EVENT 139 
#define  BPF_PROG_TYPE_RAW_TRACEPOINT 138 
#define  BPF_PROG_TYPE_SCHED_ACT 137 
#define  BPF_PROG_TYPE_SCHED_CLS 136 
#define  BPF_PROG_TYPE_SK_MSG 135 
#define  BPF_PROG_TYPE_SK_REUSEPORT 134 
#define  BPF_PROG_TYPE_SK_SKB 133 
#define  BPF_PROG_TYPE_SOCKET_FILTER 132 
#define  BPF_PROG_TYPE_SOCK_OPS 131 
#define  BPF_PROG_TYPE_TRACEPOINT 130 
#define  BPF_PROG_TYPE_UNSPEC 129 
#define  BPF_PROG_TYPE_XDP 128 

__attribute__((used)) static bool bpf_prog_type__needs_kver(enum bpf_prog_type type)
{
	switch (type) {
	case BPF_PROG_TYPE_SOCKET_FILTER:
	case BPF_PROG_TYPE_SCHED_CLS:
	case BPF_PROG_TYPE_SCHED_ACT:
	case BPF_PROG_TYPE_XDP:
	case BPF_PROG_TYPE_CGROUP_SKB:
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_LWT_IN:
	case BPF_PROG_TYPE_LWT_OUT:
	case BPF_PROG_TYPE_LWT_XMIT:
	case BPF_PROG_TYPE_LWT_SEG6LOCAL:
	case BPF_PROG_TYPE_SOCK_OPS:
	case BPF_PROG_TYPE_SK_SKB:
	case BPF_PROG_TYPE_CGROUP_DEVICE:
	case BPF_PROG_TYPE_SK_MSG:
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	case BPF_PROG_TYPE_LIRC_MODE2:
	case BPF_PROG_TYPE_SK_REUSEPORT:
		return false;
	case BPF_PROG_TYPE_UNSPEC:
	case BPF_PROG_TYPE_KPROBE:
	case BPF_PROG_TYPE_TRACEPOINT:
	case BPF_PROG_TYPE_PERF_EVENT:
	case BPF_PROG_TYPE_RAW_TRACEPOINT:
	default:
		return true;
	}
}