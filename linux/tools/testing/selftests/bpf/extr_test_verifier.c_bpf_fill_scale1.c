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
struct bpf_test {int prog_len; int retval; struct bpf_insn* fill_insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int BPF_CALL ; 
 int /*<<< orphan*/  BPF_DW ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_FUNC_get_prandom_u32 ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_JMP ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_MOV ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_RAW_INSN (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_10 ; 
 int /*<<< orphan*/  BPF_REG_6 ; 
 struct bpf_insn BPF_STX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_JMP_SEQ ; 
 int MAX_TEST_INSNS ; 
 int /*<<< orphan*/  bpf_semi_rand_get () ; 

__attribute__((used)) static void bpf_fill_scale1(struct bpf_test *self)
{
	struct bpf_insn *insn = self->fill_insns;
	int i = 0, k = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	/* test to check that the long sequence of jumps is acceptable */
	while (k++ < MAX_JMP_SEQ) {
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_get_prandom_u32);
		insn[i++] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, bpf_semi_rand_get(), 2);
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_10);
		insn[i++] = BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_6,
					-8 * (k % 64 + 1));
	}
	/* is_state_visited() doesn't allocate state for pruning for every jump.
	 * Hence multiply jmps by 4 to accommodate that heuristic
	 */
	while (i < MAX_TEST_INSNS - MAX_JMP_SEQ * 4)
		insn[i++] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 42);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
	self->retval = 42;
}