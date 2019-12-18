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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct bpf_prog {scalar_t__ len; struct bpf_insn* insnsi; } ;
struct bpf_insn {scalar_t__ src_reg; int /*<<< orphan*/  code; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_PSEUDO_CALL ; 
 int bpf_adj_delta_to_imm (struct bpf_insn*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const) ; 
 int bpf_adj_delta_to_off (struct bpf_insn*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const) ; 

__attribute__((used)) static int bpf_adj_branches(struct bpf_prog *prog, u32 pos, s32 end_old,
			    s32 end_new, const bool probe_pass)
{
	u32 i, insn_cnt = prog->len + (probe_pass ? end_new - end_old : 0);
	struct bpf_insn *insn = prog->insnsi;
	int ret = 0;

	for (i = 0; i < insn_cnt; i++, insn++) {
		u8 code;

		/* In the probing pass we still operate on the original,
		 * unpatched image in order to check overflows before we
		 * do any other adjustments. Therefore skip the patchlet.
		 */
		if (probe_pass && i == pos) {
			i = end_new;
			insn = prog->insnsi + end_old;
		}
		code = insn->code;
		if ((BPF_CLASS(code) != BPF_JMP &&
		     BPF_CLASS(code) != BPF_JMP32) ||
		    BPF_OP(code) == BPF_EXIT)
			continue;
		/* Adjust offset of jmps if we cross patch boundaries. */
		if (BPF_OP(code) == BPF_CALL) {
			if (insn->src_reg != BPF_PSEUDO_CALL)
				continue;
			ret = bpf_adj_delta_to_imm(insn, pos, end_old,
						   end_new, i, probe_pass);
		} else {
			ret = bpf_adj_delta_to_off(insn, pos, end_old,
						   end_new, i, probe_pass);
		}
		if (ret)
			break;
	}

	return ret;
}