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
typedef  int sljit_sw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int ARG_TEST ; 
 int D (int) ; 
 int /*<<< orphan*/  DR (int) ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int FD (int) ; 
 int GPR_REG ; 
 int IMM (int) ; 
 int LOAD_DATA ; 
 int MEM_MASK ; 
 int /*<<< orphan*/  MOVABLE_INS ; 
 int /*<<< orphan*/  OFFS_REG (int) ; 
 int OFFS_REG_MASK ; 
 int REG_MASK ; 
 int S1 (int) ; 
 int S2 (int /*<<< orphan*/ ) ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 int SLJIT_MEM ; 
 scalar_t__ SLJIT_UNLIKELY (int) ; 
 int* data_transfer_insts ; 
 int /*<<< orphan*/  push_inst (struct sljit_compiler*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 getput_arg_fast(struct sljit_compiler *compiler, sljit_s32 flags, sljit_s32 reg, sljit_s32 arg, sljit_sw argw)
{
	SLJIT_ASSERT(arg & SLJIT_MEM);

	if ((!(arg & OFFS_REG_MASK) && argw <= SIMM_MAX && argw >= SIMM_MIN)
			|| ((arg & OFFS_REG_MASK) && (argw & 0x3) == 0)) {
		/* Works for both absoulte and relative addresses (immediate case). */
		if (SLJIT_UNLIKELY(flags & ARG_TEST))
			return 1;
		FAIL_IF(push_inst(compiler, data_transfer_insts[flags & MEM_MASK]
			| ((flags & MEM_MASK) <= GPR_REG ? D(reg) : FD(reg))
			| S1(arg & REG_MASK) | ((arg & OFFS_REG_MASK) ? S2(OFFS_REG(arg)) : IMM(argw)),
			((flags & MEM_MASK) <= GPR_REG && (flags & LOAD_DATA)) ? DR(reg) : MOVABLE_INS));
		return -1;
	}
	return 0;
}