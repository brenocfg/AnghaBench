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
struct bpf_test {struct bpf_insn* insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct bpf_insn BPF_LD_ABS (int /*<<< orphan*/ ,int) ; 
 unsigned int BPF_MAXINSNS ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_6 ; 

__attribute__((used)) static void bpf_fill_jump_around_ld_abs(struct bpf_test *self)
{
	struct bpf_insn *insn = self->insns;
	unsigned int len = BPF_MAXINSNS;
	int i = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	insn[i++] = BPF_LD_ABS(BPF_B, 0);
	insn[i] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 10, len - i - 2);
	i++;
	while (i < len - 1)
		insn[i++] = BPF_LD_ABS(BPF_B, 1);
	insn[i] = BPF_EXIT_INSN();
}