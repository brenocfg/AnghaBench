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
struct bpf_load_program_attr {int prog_type; size_t insns_cnt; char const* license; int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  kern_version; struct bpf_insn const* insns; int /*<<< orphan*/ * name; scalar_t__ expected_attach_type; } ;
struct bpf_insn {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TEST_RND_HI32 ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,size_t) ; 
 int /*<<< orphan*/  memset (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int) ; 

int bpf_test_load_program(enum bpf_prog_type type, const struct bpf_insn *insns,
			  size_t insns_cnt, const char *license,
			  __u32 kern_version, char *log_buf,
		     size_t log_buf_sz)
{
	struct bpf_load_program_attr load_attr;

	memset(&load_attr, 0, sizeof(struct bpf_load_program_attr));
	load_attr.prog_type = type;
	load_attr.expected_attach_type = 0;
	load_attr.name = NULL;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = license;
	load_attr.kern_version = kern_version;
	load_attr.prog_flags = BPF_F_TEST_RND_HI32;

	return bpf_load_program_xattr(&load_attr, log_buf, log_buf_sz);
}