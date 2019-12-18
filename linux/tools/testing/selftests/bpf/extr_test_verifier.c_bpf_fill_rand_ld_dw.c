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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bpf_test {int retval; int prog_len; struct bpf_insn* fill_insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_ALU64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 struct bpf_insn BPF_LD_IMM64 (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_MOV32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_RSH ; 
 int /*<<< orphan*/  BPF_XOR ; 
 int bpf_semi_rand_get () ; 

__attribute__((used)) static void bpf_fill_rand_ld_dw(struct bpf_test *self)
{
	struct bpf_insn *insn = self->fill_insns;
	uint64_t res = 0;
	int i = 0;

	insn[i++] = BPF_MOV32_IMM(BPF_REG_0, 0);
	while (i < self->retval) {
		uint64_t val = bpf_semi_rand_get();
		struct bpf_insn tmp[2] = { BPF_LD_IMM64(BPF_REG_1, val) };

		res ^= val;
		insn[i++] = tmp[0];
		insn[i++] = tmp[1];
		insn[i++] = BPF_ALU64_REG(BPF_XOR, BPF_REG_0, BPF_REG_1);
	}
	insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	insn[i++] = BPF_ALU64_IMM(BPF_RSH, BPF_REG_1, 32);
	insn[i++] = BPF_ALU64_REG(BPF_XOR, BPF_REG_0, BPF_REG_1);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
	res ^= (res >> 32);
	self->retval = (uint32_t)res;
}