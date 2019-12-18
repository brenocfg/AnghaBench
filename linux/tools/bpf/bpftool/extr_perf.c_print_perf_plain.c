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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
#define  BPF_FD_TYPE_KPROBE 133 
#define  BPF_FD_TYPE_KRETPROBE 132 
#define  BPF_FD_TYPE_RAW_TRACEPOINT 131 
#define  BPF_FD_TYPE_TRACEPOINT 130 
#define  BPF_FD_TYPE_UPROBE 129 
#define  BPF_FD_TYPE_URETPROBE 128 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_perf_plain(int pid, int fd, __u32 prog_id, __u32 fd_type,
			     char *buf, __u64 probe_offset, __u64 probe_addr)
{
	printf("pid %d  fd %d: prog_id %u  ", pid, fd, prog_id);
	switch (fd_type) {
	case BPF_FD_TYPE_RAW_TRACEPOINT:
		printf("raw_tracepoint  %s\n", buf);
		break;
	case BPF_FD_TYPE_TRACEPOINT:
		printf("tracepoint  %s\n", buf);
		break;
	case BPF_FD_TYPE_KPROBE:
		if (buf[0] != '\0')
			printf("kprobe  func %s  offset %llu\n", buf,
			       probe_offset);
		else
			printf("kprobe  addr %llu\n", probe_addr);
		break;
	case BPF_FD_TYPE_KRETPROBE:
		if (buf[0] != '\0')
			printf("kretprobe  func %s  offset %llu\n", buf,
			       probe_offset);
		else
			printf("kretprobe  addr %llu\n", probe_addr);
		break;
	case BPF_FD_TYPE_UPROBE:
		printf("uprobe  filename %s  offset %llu\n", buf, probe_offset);
		break;
	case BPF_FD_TYPE_URETPROBE:
		printf("uretprobe  filename %s  offset %llu\n", buf,
		       probe_offset);
		break;
	default:
		break;
	}
}