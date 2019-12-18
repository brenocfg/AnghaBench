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
struct sljit_compiler {int skip_checks; } ;
typedef  scalar_t__ sljit_sw ;
typedef  int /*<<< orphan*/  sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_LOCAL_OFFSET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_ERROR () ; 
 int /*<<< orphan*/  SLJIT_ADD ; 
 int /*<<< orphan*/  SLJIT_IMM ; 
 int /*<<< orphan*/  SLJIT_MEM1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLJIT_MOV ; 
 int /*<<< orphan*/  SLJIT_SP ; 
 int /*<<< orphan*/  check_sljit_get_local_base (struct sljit_compiler*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sljit_emit_op1 (struct sljit_compiler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sljit_emit_op2 (struct sljit_compiler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

sljit_s32 sljit_get_local_base(struct sljit_compiler *compiler, sljit_s32 dst, sljit_sw dstw, sljit_sw offset)
{
	CHECK_ERROR();
	CHECK(check_sljit_get_local_base(compiler, dst, dstw, offset));

	ADJUST_LOCAL_OFFSET(SLJIT_MEM1(SLJIT_SP), offset);
#if (defined SLJIT_VERBOSE && SLJIT_VERBOSE) \
		|| (defined SLJIT_ARGUMENT_CHECKS && SLJIT_ARGUMENT_CHECKS)
	compiler->skip_checks = 1;
#endif
	if (offset != 0)
		return sljit_emit_op2(compiler, SLJIT_ADD, dst, dstw, SLJIT_SP, 0, SLJIT_IMM, offset);
	return sljit_emit_op1(compiler, SLJIT_MOV, dst, dstw, SLJIT_SP, 0);
}