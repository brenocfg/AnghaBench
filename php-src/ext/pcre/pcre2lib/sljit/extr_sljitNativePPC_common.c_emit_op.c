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
struct sljit_compiler {int dummy; } ;
typedef  int /*<<< orphan*/  sljit_sw ;
typedef  scalar_t__ sljit_s32 ;

/* Variables and functions */
 scalar_t__ ALT_FORM1 ; 
 scalar_t__ ALT_FORM2 ; 
 scalar_t__ ALT_FORM3 ; 
 scalar_t__ ALT_FORM4 ; 
 scalar_t__ ALT_FORM5 ; 
 scalar_t__ ALT_SET_FLAGS ; 
 scalar_t__ ALT_SIGN_EXT ; 
 int /*<<< orphan*/  FAIL_IF (scalar_t__) ; 
 scalar_t__ FAST_IS_REG (scalar_t__) ; 
 scalar_t__ LOAD_DATA ; 
 scalar_t__ REG1_SOURCE ; 
 scalar_t__ REG2_SOURCE ; 
 scalar_t__ REG_DEST ; 
 scalar_t__ SLJIT_IMM ; 
 scalar_t__ SLJIT_MEM ; 
 scalar_t__ SLJIT_MOV ; 
 scalar_t__ SLJIT_MOV_P ; 
 scalar_t__ SLJIT_SUCCESS ; 
 scalar_t__ SLOW_IS_REG (scalar_t__) ; 
 scalar_t__ TMP_REG1 ; 
 scalar_t__ TMP_REG2 ; 
 scalar_t__ emit_op_mem (struct sljit_compiler*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ emit_single_op (struct sljit_compiler*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ load_immediate (struct sljit_compiler*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 emit_op(struct sljit_compiler *compiler, sljit_s32 op, sljit_s32 input_flags,
	sljit_s32 dst, sljit_sw dstw,
	sljit_s32 src1, sljit_sw src1w,
	sljit_s32 src2, sljit_sw src2w)
{
	/* arg1 goes to TMP_REG1 or src reg
	   arg2 goes to TMP_REG2, imm or src reg
	   result goes to TMP_REG2, so put result can use TMP_REG1. */
	sljit_s32 dst_r = TMP_REG2;
	sljit_s32 src1_r;
	sljit_s32 src2_r;
	sljit_s32 sugg_src2_r = TMP_REG2;
	sljit_s32 flags = input_flags & (ALT_FORM1 | ALT_FORM2 | ALT_FORM3 | ALT_FORM4 | ALT_FORM5 | ALT_SIGN_EXT | ALT_SET_FLAGS);

	/* Destination check. */
	if (SLOW_IS_REG(dst)) {
		dst_r = dst;
		flags |= REG_DEST;

		if (op >= SLJIT_MOV && op <= SLJIT_MOV_P)
			sugg_src2_r = dst_r;
	}

	/* Source 1. */
	if (FAST_IS_REG(src1)) {
		src1_r = src1;
		flags |= REG1_SOURCE;
	}
	else if (src1 & SLJIT_IMM) {
		FAIL_IF(load_immediate(compiler, TMP_REG1, src1w));
		src1_r = TMP_REG1;
	}
	else {
		FAIL_IF(emit_op_mem(compiler, input_flags | LOAD_DATA, TMP_REG1, src1, src1w, TMP_REG1));
		src1_r = TMP_REG1;
	}

	/* Source 2. */
	if (FAST_IS_REG(src2)) {
		src2_r = src2;
		flags |= REG2_SOURCE;

		if (!(flags & REG_DEST) && op >= SLJIT_MOV && op <= SLJIT_MOV_P)
			dst_r = src2_r;
	}
	else if (src2 & SLJIT_IMM) {
		FAIL_IF(load_immediate(compiler, sugg_src2_r, src2w));
		src2_r = sugg_src2_r;
	}
	else {
		FAIL_IF(emit_op_mem(compiler, input_flags | LOAD_DATA, sugg_src2_r, src2, src2w, TMP_REG2));
		src2_r = sugg_src2_r;
	}

	FAIL_IF(emit_single_op(compiler, op, flags, dst_r, src1_r, src2_r));

	if (!(dst & SLJIT_MEM))
		return SLJIT_SUCCESS;

	return emit_op_mem(compiler, input_flags, dst_r, dst, dstw, TMP_REG1);
}