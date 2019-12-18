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
union bpf_attr {int prog_type; size_t log_size; int log_level; void* prog_flags; void* kern_version; void* log_buf; void* license; void* insns; void* insn_cnt; } ;
typedef  char bpf_insn ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  attr ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 void* ptr_to_u64 (char const*) ; 
 int sys_bpf_prog_load (union bpf_attr*,int) ; 

int bpf_verify_program(enum bpf_prog_type type, const struct bpf_insn *insns,
		       size_t insns_cnt, __u32 prog_flags, const char *license,
		       __u32 kern_version, char *log_buf, size_t log_buf_sz,
		       int log_level)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.prog_type = type;
	attr.insn_cnt = (__u32)insns_cnt;
	attr.insns = ptr_to_u64(insns);
	attr.license = ptr_to_u64(license);
	attr.log_buf = ptr_to_u64(log_buf);
	attr.log_size = log_buf_sz;
	attr.log_level = log_level;
	log_buf[0] = 0;
	attr.kern_version = kern_version;
	attr.prog_flags = prog_flags;

	return sys_bpf_prog_load(&attr, sizeof(attr));
}