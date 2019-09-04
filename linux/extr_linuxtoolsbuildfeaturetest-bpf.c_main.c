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
union bpf_attr {scalar_t__ prog_flags; scalar_t__ kern_version; scalar_t__ log_level; scalar_t__ log_size; scalar_t__ log_buf; scalar_t__ license; scalar_t__ insns; scalar_t__ insn_cnt; int /*<<< orphan*/  prog_type; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_LOAD ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_KPROBE ; 
 int /*<<< orphan*/  __NR_bpf ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int main(void)
{
	union bpf_attr attr;

	/* Check fields in attr */
	attr.prog_type = BPF_PROG_TYPE_KPROBE;
	attr.insn_cnt = 0;
	attr.insns = 0;
	attr.license = 0;
	attr.log_buf = 0;
	attr.log_size = 0;
	attr.log_level = 0;
	attr.kern_version = 0;
	attr.prog_flags = 0;

	/*
	 * Test existence of __NR_bpf and BPF_PROG_LOAD.
	 * This call should fail if we run the testcase.
	 */
	return syscall(__NR_bpf, BPF_PROG_LOAD, &attr, sizeof(attr));
}