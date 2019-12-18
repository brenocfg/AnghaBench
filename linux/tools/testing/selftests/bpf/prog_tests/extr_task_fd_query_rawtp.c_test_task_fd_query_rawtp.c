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
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int BPF_FD_TYPE_RAW_TRACEPOINT ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_RAW_TRACEPOINT ; 
 scalar_t__ CHECK (int,char*,char*,int,...) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 int bpf_prog_load (char const*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 int bpf_raw_tracepoint_open (char*,int) ; 
 int bpf_task_fd_query (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

void test_task_fd_query_rawtp(void)
{
	const char *file = "./test_get_stack_rawtp.o";
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	struct bpf_object *obj;
	int efd, err, prog_fd;
	__u32 duration = 0;
	char buf[256];

	err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	if (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, errno))
		return;

	efd = bpf_raw_tracepoint_open("sys_enter", prog_fd);
	if (CHECK(efd < 0, "raw_tp_open", "err %d errno %d\n", efd, errno))
		goto close_prog;

	/* query (getpid(), efd) */
	len = sizeof(buf);
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	if (CHECK(err < 0, "bpf_task_fd_query", "err %d errno %d\n", err,
		  errno))
		goto close_prog;

	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      strcmp(buf, "sys_enter") == 0;
	if (CHECK(!err, "check_results", "fd_type %d tp_name %s\n",
		  fd_type, buf))
		goto close_prog;

	/* test zero len */
	len = 0;
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	if (CHECK(err < 0, "bpf_task_fd_query (len = 0)", "err %d errno %d\n",
		  err, errno))
		goto close_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == strlen("sys_enter");
	if (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		goto close_prog;

	/* test empty buffer */
	len = sizeof(buf);
	err = bpf_task_fd_query(getpid(), efd, 0, 0, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	if (CHECK(err < 0, "bpf_task_fd_query (buf = 0)", "err %d errno %d\n",
		  err, errno))
		goto close_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == strlen("sys_enter");
	if (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		goto close_prog;

	/* test smaller buffer */
	len = 3;
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	if (CHECK(err >= 0 || errno != ENOSPC, "bpf_task_fd_query (len = 3)",
		  "err %d errno %d\n", err, errno))
		goto close_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == strlen("sys_enter") &&
	      strcmp(buf, "sy") == 0;
	if (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		goto close_prog;

close_prog:
	bpf_object__close(obj);
}