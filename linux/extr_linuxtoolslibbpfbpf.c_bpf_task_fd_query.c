#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pid; int fd; int /*<<< orphan*/  probe_addr; int /*<<< orphan*/  probe_offset; void* fd_type; void* prog_id; void* buf_len; int /*<<< orphan*/  buf; void* flags; } ;
union bpf_attr {TYPE_1__ task_fd_query; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_TASK_FD_QUERY ; 
 int /*<<< orphan*/  ptr_to_u64 (char*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_task_fd_query(int pid, int fd, __u32 flags, char *buf, __u32 *buf_len,
		      __u32 *prog_id, __u32 *fd_type, __u64 *probe_offset,
		      __u64 *probe_addr)
{
	union bpf_attr attr = {};
	int err;

	attr.task_fd_query.pid = pid;
	attr.task_fd_query.fd = fd;
	attr.task_fd_query.flags = flags;
	attr.task_fd_query.buf = ptr_to_u64(buf);
	attr.task_fd_query.buf_len = *buf_len;

	err = sys_bpf(BPF_TASK_FD_QUERY, &attr, sizeof(attr));
	*buf_len = attr.task_fd_query.buf_len;
	*prog_id = attr.task_fd_query.prog_id;
	*fd_type = attr.task_fd_query.fd_type;
	*probe_offset = attr.task_fd_query.probe_offset;
	*probe_addr = attr.task_fd_query.probe_addr;

	return err;
}