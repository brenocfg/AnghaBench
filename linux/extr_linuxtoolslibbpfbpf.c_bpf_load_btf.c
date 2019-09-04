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
union bpf_attr {int btf_log_level; void* btf_log_buf; void* btf_log_size; void* btf_size; void* btf; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_BTF_LOAD ; 
 void* ptr_to_u64 (char*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_load_btf(void *btf, __u32 btf_size, char *log_buf, __u32 log_buf_size,
		 bool do_log)
{
	union bpf_attr attr = {};
	int fd;

	attr.btf = ptr_to_u64(btf);
	attr.btf_size = btf_size;

retry:
	if (do_log && log_buf && log_buf_size) {
		attr.btf_log_level = 1;
		attr.btf_log_size = log_buf_size;
		attr.btf_log_buf = ptr_to_u64(log_buf);
	}

	fd = sys_bpf(BPF_BTF_LOAD, &attr, sizeof(attr));
	if (fd == -1 && !do_log && log_buf && log_buf_size) {
		do_log = true;
		goto retry;
	}

	return fd;
}