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
typedef  scalar_t__ u8 ;
struct bpf_insn_pos {struct bpf_insn* pos; struct bpf_insn* begin; } ;
struct bpf_insn {int off; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_JMP ; 
 int BPF_LOADER_ERRNO__PROLOGUE ; 
 int BPF_LOADER_ERRNO__PROLOGUE2BIG ; 
 scalar_t__ BPF_OP (int /*<<< orphan*/ ) ; 
#define  JMP_TO_ERROR_CODE 130 
#define  JMP_TO_SUCCESS_CODE 129 
#define  JMP_TO_USER_CODE 128 
 scalar_t__ check_pos (struct bpf_insn_pos*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
prologue_relocate(struct bpf_insn_pos *pos, struct bpf_insn *error_code,
		  struct bpf_insn *success_code, struct bpf_insn *user_code)
{
	struct bpf_insn *insn;

	if (check_pos(pos))
		return -BPF_LOADER_ERRNO__PROLOGUE2BIG;

	for (insn = pos->begin; insn < pos->pos; insn++) {
		struct bpf_insn *target;
		u8 class = BPF_CLASS(insn->code);
		u8 opcode;

		if (class != BPF_JMP)
			continue;
		opcode = BPF_OP(insn->code);
		if (opcode == BPF_CALL)
			continue;

		switch (insn->off) {
		case JMP_TO_ERROR_CODE:
			target = error_code;
			break;
		case JMP_TO_SUCCESS_CODE:
			target = success_code;
			break;
		case JMP_TO_USER_CODE:
			target = user_code;
			break;
		default:
			pr_err("bpf prologue: internal error: relocation failed\n");
			return -BPF_LOADER_ERRNO__PROLOGUE;
		}

		insn->off = target - (insn + 1);
	}
	return 0;
}