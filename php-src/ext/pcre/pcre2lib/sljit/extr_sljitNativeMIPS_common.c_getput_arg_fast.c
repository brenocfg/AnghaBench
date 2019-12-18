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
typedef  scalar_t__ sljit_sw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int ARG_TEST ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int GPR_REG ; 
 int IMM (scalar_t__) ; 
 int LOAD_DATA ; 
 int MEM_MASK ; 
 int MOVABLE_INS ; 
 int OFFS_REG_MASK ; 
 int REG_MASK ; 
 int S (int) ; 
 scalar_t__ SIMM_MAX ; 
 scalar_t__ SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 int SLJIT_MEM ; 
 scalar_t__ SLJIT_UNLIKELY (int) ; 
 int TA (int) ; 
 int* data_transfer_insts ; 
 int /*<<< orphan*/  push_inst (struct sljit_compiler*,int,int) ; 

__attribute__((used)) static sljit_s32 getput_arg_fast(struct sljit_compiler *compiler, sljit_s32 flags, sljit_s32 reg_ar, sljit_s32 arg, sljit_sw argw)
{
	SLJIT_ASSERT(arg & SLJIT_MEM);

	if (!(arg & OFFS_REG_MASK) && argw <= SIMM_MAX && argw >= SIMM_MIN) {
		/* Works for both absoulte and relative addresses. */
		if (SLJIT_UNLIKELY(flags & ARG_TEST))
			return 1;
		FAIL_IF(push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(arg & REG_MASK)
			| TA(reg_ar) | IMM(argw), ((flags & MEM_MASK) <= GPR_REG && (flags & LOAD_DATA)) ? reg_ar : MOVABLE_INS));
		return -1;
	}
	return 0;
}