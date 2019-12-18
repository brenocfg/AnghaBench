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
struct sock_addr_test {int dummy; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  insns ;

/* Variables and functions */
 struct bpf_insn BPF_EXIT_INSN () ; 
 struct bpf_insn BPF_MOV64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int load_insns (struct sock_addr_test const*,struct bpf_insn*,int) ; 

__attribute__((used)) static int xmsg_ret_only_prog_load(const struct sock_addr_test *test,
				   int32_t rc)
{
	struct bpf_insn insns[] = {
		/* return rc */
		BPF_MOV64_IMM(BPF_REG_0, rc),
		BPF_EXIT_INSN(),
	};
	return load_insns(test, insns, sizeof(insns) / sizeof(struct bpf_insn));
}