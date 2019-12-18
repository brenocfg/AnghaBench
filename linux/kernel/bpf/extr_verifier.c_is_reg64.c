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
typedef  scalar_t__ u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {scalar_t__ type; } ;
struct bpf_insn {scalar_t__ code; scalar_t__ src_reg; int imm; } ;
typedef  enum reg_arg_type { ____Placeholder_reg_arg_type } reg_arg_type ;

/* Variables and functions */
 scalar_t__ BPF_ALU ; 
 scalar_t__ BPF_ALU64 ; 
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (scalar_t__) ; 
 scalar_t__ BPF_DW ; 
 scalar_t__ BPF_END ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_IMM ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 scalar_t__ BPF_MODE (scalar_t__) ; 
 scalar_t__ BPF_OP (scalar_t__) ; 
 scalar_t__ BPF_PSEUDO_CALL ; 
 scalar_t__ BPF_REG_6 ; 
 scalar_t__ BPF_SIZE (scalar_t__) ; 
 scalar_t__ BPF_ST ; 
 scalar_t__ BPF_STX ; 
 scalar_t__ SCALAR_VALUE ; 
 int SRC_OP ; 

__attribute__((used)) static bool is_reg64(struct bpf_verifier_env *env, struct bpf_insn *insn,
		     u32 regno, struct bpf_reg_state *reg, enum reg_arg_type t)
{
	u8 code, class, op;

	code = insn->code;
	class = BPF_CLASS(code);
	op = BPF_OP(code);
	if (class == BPF_JMP) {
		/* BPF_EXIT for "main" will reach here. Return TRUE
		 * conservatively.
		 */
		if (op == BPF_EXIT)
			return true;
		if (op == BPF_CALL) {
			/* BPF to BPF call will reach here because of marking
			 * caller saved clobber with DST_OP_NO_MARK for which we
			 * don't care the register def because they are anyway
			 * marked as NOT_INIT already.
			 */
			if (insn->src_reg == BPF_PSEUDO_CALL)
				return false;
			/* Helper call will reach here because of arg type
			 * check, conservatively return TRUE.
			 */
			if (t == SRC_OP)
				return true;

			return false;
		}
	}

	if (class == BPF_ALU64 || class == BPF_JMP ||
	    /* BPF_END always use BPF_ALU class. */
	    (class == BPF_ALU && op == BPF_END && insn->imm == 64))
		return true;

	if (class == BPF_ALU || class == BPF_JMP32)
		return false;

	if (class == BPF_LDX) {
		if (t != SRC_OP)
			return BPF_SIZE(code) == BPF_DW;
		/* LDX source must be ptr. */
		return true;
	}

	if (class == BPF_STX) {
		if (reg->type != SCALAR_VALUE)
			return true;
		return BPF_SIZE(code) == BPF_DW;
	}

	if (class == BPF_LD) {
		u8 mode = BPF_MODE(code);

		/* LD_IMM64 */
		if (mode == BPF_IMM)
			return true;

		/* Both LD_IND and LD_ABS return 32-bit data. */
		if (t != SRC_OP)
			return  false;

		/* Implicit ctx ptr. */
		if (regno == BPF_REG_6)
			return true;

		/* Explicit source could be any width. */
		return true;
	}

	if (class == BPF_ST)
		/* The only source register for BPF_ST is a ptr. */
		return true;

	/* Conservatively return true at default. */
	return true;
}