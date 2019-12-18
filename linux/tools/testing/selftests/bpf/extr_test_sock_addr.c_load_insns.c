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
struct sock_addr_test {scalar_t__ expected_result; int /*<<< orphan*/  expected_attach_type; } ;
struct bpf_load_program_attr {size_t insns_cnt; char* license; struct bpf_insn const* insns; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_CGROUP_SOCK_ADDR ; 
 scalar_t__ LOAD_REJECT ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_log_buf ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int load_insns(const struct sock_addr_test *test,
		      const struct bpf_insn *insns, size_t insns_cnt)
{
	struct bpf_load_program_attr load_attr;
	int ret;

	memset(&load_attr, 0, sizeof(struct bpf_load_program_attr));
	load_attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
	load_attr.expected_attach_type = test->expected_attach_type;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = "GPL";

	ret = bpf_load_program_xattr(&load_attr, bpf_log_buf, BPF_LOG_BUF_SIZE);
	if (ret < 0 && test->expected_result != LOAD_REJECT) {
		log_err(">>> Loading program error.\n"
			">>> Verifier output:\n%s\n-------\n", bpf_log_buf);
	}

	return ret;
}