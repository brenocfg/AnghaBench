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
struct bpf_load_program_attr {int prog_type; size_t insns_cnt; char* license; int /*<<< orphan*/  prog_ifindex; struct bpf_insn const* insns; int /*<<< orphan*/  kern_version; int /*<<< orphan*/  expected_attach_type; } ;
struct bpf_insn {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_INET4_CONNECT ; 
#define  BPF_PROG_TYPE_CGROUP_DEVICE 153 
#define  BPF_PROG_TYPE_CGROUP_SKB 152 
#define  BPF_PROG_TYPE_CGROUP_SOCK 151 
#define  BPF_PROG_TYPE_CGROUP_SOCKOPT 150 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 149 
#define  BPF_PROG_TYPE_CGROUP_SYSCTL 148 
#define  BPF_PROG_TYPE_FLOW_DISSECTOR 147 
#define  BPF_PROG_TYPE_KPROBE 146 
#define  BPF_PROG_TYPE_LIRC_MODE2 145 
#define  BPF_PROG_TYPE_LWT_IN 144 
#define  BPF_PROG_TYPE_LWT_OUT 143 
#define  BPF_PROG_TYPE_LWT_SEG6LOCAL 142 
#define  BPF_PROG_TYPE_LWT_XMIT 141 
#define  BPF_PROG_TYPE_PERF_EVENT 140 
#define  BPF_PROG_TYPE_RAW_TRACEPOINT 139 
#define  BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE 138 
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
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_kernel_version () ; 

__attribute__((used)) static void
probe_load(enum bpf_prog_type prog_type, const struct bpf_insn *insns,
	   size_t insns_cnt, char *buf, size_t buf_len, __u32 ifindex)
{
	struct bpf_load_program_attr xattr = {};
	int fd;

	switch (prog_type) {
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		xattr.expected_attach_type = BPF_CGROUP_INET4_CONNECT;
		break;
	case BPF_PROG_TYPE_KPROBE:
		xattr.kern_version = get_kernel_version();
		break;
	case BPF_PROG_TYPE_UNSPEC:
	case BPF_PROG_TYPE_SOCKET_FILTER:
	case BPF_PROG_TYPE_SCHED_CLS:
	case BPF_PROG_TYPE_SCHED_ACT:
	case BPF_PROG_TYPE_TRACEPOINT:
	case BPF_PROG_TYPE_XDP:
	case BPF_PROG_TYPE_PERF_EVENT:
	case BPF_PROG_TYPE_CGROUP_SKB:
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_LWT_IN:
	case BPF_PROG_TYPE_LWT_OUT:
	case BPF_PROG_TYPE_LWT_XMIT:
	case BPF_PROG_TYPE_SOCK_OPS:
	case BPF_PROG_TYPE_SK_SKB:
	case BPF_PROG_TYPE_CGROUP_DEVICE:
	case BPF_PROG_TYPE_SK_MSG:
	case BPF_PROG_TYPE_RAW_TRACEPOINT:
	case BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE:
	case BPF_PROG_TYPE_LWT_SEG6LOCAL:
	case BPF_PROG_TYPE_LIRC_MODE2:
	case BPF_PROG_TYPE_SK_REUSEPORT:
	case BPF_PROG_TYPE_FLOW_DISSECTOR:
	case BPF_PROG_TYPE_CGROUP_SYSCTL:
	case BPF_PROG_TYPE_CGROUP_SOCKOPT:
	default:
		break;
	}

	xattr.prog_type = prog_type;
	xattr.insns = insns;
	xattr.insns_cnt = insns_cnt;
	xattr.license = "GPL";
	xattr.prog_ifindex = ifindex;

	fd = bpf_load_program_xattr(&xattr, buf, buf_len);
	if (fd >= 0)
		close(fd);
}