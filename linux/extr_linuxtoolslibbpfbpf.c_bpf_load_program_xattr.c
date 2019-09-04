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
union bpf_attr {size_t log_size; int log_level; void* log_buf; int /*<<< orphan*/  prog_name; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  kern_version; void* license; void* insns; scalar_t__ insn_cnt; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_load_program_attr {char* insns; char* license; int /*<<< orphan*/  name; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  kern_version; scalar_t__ insns_cnt; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ BPF_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  BPF_PROG_LOAD ; 
 int EINVAL ; 
 int /*<<< orphan*/  bzero (union bpf_attr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 void* ptr_to_u64 (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_load_program_xattr(const struct bpf_load_program_attr *load_attr,
			   char *log_buf, size_t log_buf_sz)
{
	union bpf_attr attr;
	__u32 name_len;
	int fd;

	if (!load_attr)
		return -EINVAL;

	name_len = load_attr->name ? strlen(load_attr->name) : 0;

	bzero(&attr, sizeof(attr));
	attr.prog_type = load_attr->prog_type;
	attr.expected_attach_type = load_attr->expected_attach_type;
	attr.insn_cnt = (__u32)load_attr->insns_cnt;
	attr.insns = ptr_to_u64(load_attr->insns);
	attr.license = ptr_to_u64(load_attr->license);
	attr.log_buf = ptr_to_u64(NULL);
	attr.log_size = 0;
	attr.log_level = 0;
	attr.kern_version = load_attr->kern_version;
	attr.prog_ifindex = load_attr->prog_ifindex;
	memcpy(attr.prog_name, load_attr->name,
	       min(name_len, BPF_OBJ_NAME_LEN - 1));

	fd = sys_bpf(BPF_PROG_LOAD, &attr, sizeof(attr));
	if (fd >= 0 || !log_buf || !log_buf_sz)
		return fd;

	/* Try again with log */
	attr.log_buf = ptr_to_u64(log_buf);
	attr.log_size = log_buf_sz;
	attr.log_level = 1;
	log_buf[0] = 0;
	return sys_bpf(BPF_PROG_LOAD, &attr, sizeof(attr));
}