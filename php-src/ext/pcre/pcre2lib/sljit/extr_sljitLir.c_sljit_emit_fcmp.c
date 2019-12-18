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
struct sljit_jump {int dummy; } ;
struct sljit_compiler {int skip_checks; } ;
typedef  int /*<<< orphan*/  sljit_sw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR_PTR () ; 
 int /*<<< orphan*/  CHECK_PTR (int /*<<< orphan*/ ) ; 
 int SLJIT_CMP_F64 ; 
 int SLJIT_I32_OP ; 
 int VARIABLE_FLAG_SHIFT ; 
 int /*<<< orphan*/  check_sljit_emit_fcmp (struct sljit_compiler*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sljit_emit_fop1 (struct sljit_compiler*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sljit_jump* sljit_emit_jump (struct sljit_compiler*,int) ; 

struct sljit_jump* sljit_emit_fcmp(struct sljit_compiler *compiler, sljit_s32 type,
	sljit_s32 src1, sljit_sw src1w,
	sljit_s32 src2, sljit_sw src2w)
{
	CHECK_ERROR_PTR();
	CHECK_PTR(check_sljit_emit_fcmp(compiler, type, src1, src1w, src2, src2w));

#if (defined SLJIT_VERBOSE && SLJIT_VERBOSE) \
		|| (defined SLJIT_ARGUMENT_CHECKS && SLJIT_ARGUMENT_CHECKS)
	compiler->skip_checks = 1;
#endif
	sljit_emit_fop1(compiler, SLJIT_CMP_F64 | ((type & 0xff) << VARIABLE_FLAG_SHIFT) | (type & SLJIT_I32_OP), src1, src1w, src2, src2w);

#if (defined SLJIT_VERBOSE && SLJIT_VERBOSE) \
		|| (defined SLJIT_ARGUMENT_CHECKS && SLJIT_ARGUMENT_CHECKS)
	compiler->skip_checks = 1;
#endif
	return sljit_emit_jump(compiler, type);
}