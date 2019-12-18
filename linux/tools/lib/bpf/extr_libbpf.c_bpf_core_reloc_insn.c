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
struct bpf_program {struct bpf_insn* insns; } ;
struct bpf_insn {scalar_t__ imm; int /*<<< orphan*/  off; int /*<<< orphan*/  dst_reg; int /*<<< orphan*/  src_reg; int /*<<< orphan*/  code; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ BPF_ALU ; 
 scalar_t__ BPF_ALU64 ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_K ; 
 scalar_t__ BPF_SRC (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bpf_program__title (struct bpf_program*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bpf_core_reloc_insn(struct bpf_program *prog, int insn_off,
			       __u32 orig_off, __u32 new_off)
{
	struct bpf_insn *insn;
	int insn_idx;
	__u8 class;

	if (insn_off % sizeof(struct bpf_insn))
		return -EINVAL;
	insn_idx = insn_off / sizeof(struct bpf_insn);

	insn = &prog->insns[insn_idx];
	class = BPF_CLASS(insn->code);

	if (class == BPF_ALU || class == BPF_ALU64) {
		if (BPF_SRC(insn->code) != BPF_K)
			return -EINVAL;
		if (insn->imm != orig_off)
			return -EINVAL;
		insn->imm = new_off;
		pr_debug("prog '%s': patched insn #%d (ALU/ALU64) imm %d -> %d\n",
			 bpf_program__title(prog, false),
			 insn_idx, orig_off, new_off);
	} else {
		pr_warning("prog '%s': trying to relocate unrecognized insn #%d, code:%x, src:%x, dst:%x, off:%x, imm:%x\n",
			   bpf_program__title(prog, false),
			   insn_idx, insn->code, insn->src_reg, insn->dst_reg,
			   insn->off, insn->imm);
		return -EINVAL;
	}
	return 0;
}