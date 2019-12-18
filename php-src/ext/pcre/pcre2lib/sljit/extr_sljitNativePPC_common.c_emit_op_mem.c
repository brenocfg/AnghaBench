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
typedef  size_t sljit_s32 ;
typedef  int sljit_ins ;

/* Variables and functions */
 int A (size_t) ; 
 int ADDIS ; 
 int B (size_t) ; 
 int D (size_t) ; 
 int /*<<< orphan*/  FAIL_IF (size_t) ; 
 int IMM (int) ; 
 size_t INDEXED ; 
 int INST_CODE_AND_DST (int,size_t,size_t) ; 
 int INT_ALIGNED ; 
 size_t MEM_MASK ; 
 size_t OFFS_REG (size_t) ; 
 size_t OFFS_REG_MASK ; 
 size_t REG_MASK ; 
 int RLDI (size_t,size_t,int,int,int) ; 
 int RLWINM ; 
 int S (size_t) ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 size_t SLJIT_MEM ; 
 scalar_t__ SLJIT_UNLIKELY (size_t) ; 
 int* data_transfer_insts ; 
 size_t load_immediate (struct sljit_compiler*,size_t,int) ; 
 size_t push_inst (struct sljit_compiler*,int) ; 

__attribute__((used)) static sljit_s32 emit_op_mem(struct sljit_compiler *compiler, sljit_s32 inp_flags, sljit_s32 reg,
	sljit_s32 arg, sljit_sw argw, sljit_s32 tmp_reg)
{
	sljit_ins inst;
	sljit_s32 offs_reg;
	sljit_sw high_short;

	/* Should work when (arg & REG_MASK) == 0. */
	SLJIT_ASSERT(A(0) == 0);
	SLJIT_ASSERT(arg & SLJIT_MEM);

	if (SLJIT_UNLIKELY(arg & OFFS_REG_MASK)) {
		argw &= 0x3;
		offs_reg = OFFS_REG(arg);

		if (argw != 0) {
#if (defined SLJIT_CONFIG_PPC_32 && SLJIT_CONFIG_PPC_32)
			FAIL_IF(push_inst(compiler, RLWINM | S(OFFS_REG(arg)) | A(tmp_reg) | (argw << 11) | ((31 - argw) << 1)));
#else
			FAIL_IF(push_inst(compiler, RLDI(tmp_reg, OFFS_REG(arg), argw, 63 - argw, 1)));
#endif
			offs_reg = tmp_reg;
		}

		inst = data_transfer_insts[(inp_flags | INDEXED) & MEM_MASK];

#if (defined SLJIT_CONFIG_PPC_64 && SLJIT_CONFIG_PPC_64)
		SLJIT_ASSERT(!(inst & INT_ALIGNED));
#endif

		return push_inst(compiler, INST_CODE_AND_DST(inst, inp_flags, reg) | A(arg & REG_MASK) | B(offs_reg));
	}

	inst = data_transfer_insts[inp_flags & MEM_MASK];
	arg &= REG_MASK;

#if (defined SLJIT_CONFIG_PPC_64 && SLJIT_CONFIG_PPC_64)
	if ((inst & INT_ALIGNED) && (argw & 0x3) != 0) {
		FAIL_IF(load_immediate(compiler, tmp_reg, argw));

		inst = data_transfer_insts[(inp_flags | INDEXED) & MEM_MASK];
		return push_inst(compiler, INST_CODE_AND_DST(inst, inp_flags, reg) | A(arg) | B(tmp_reg));
	}
#endif

	if (argw <= SIMM_MAX && argw >= SIMM_MIN)
		return push_inst(compiler, INST_CODE_AND_DST(inst, inp_flags, reg) | A(arg) | IMM(argw));

#if (defined SLJIT_CONFIG_PPC_64 && SLJIT_CONFIG_PPC_64)
	if (argw <= 0x7fff7fffl && argw >= -0x80000000l) {
#endif

		high_short = (sljit_s32)(argw + ((argw & 0x8000) << 1)) & ~0xffff;

#if (defined SLJIT_CONFIG_PPC_64 && SLJIT_CONFIG_PPC_64)
		SLJIT_ASSERT(high_short && high_short <= 0x7fffffffl && high_short >= -0x80000000l);
#else
		SLJIT_ASSERT(high_short);
#endif

		FAIL_IF(push_inst(compiler, ADDIS | D(tmp_reg) | A(arg) | IMM(high_short >> 16)));
		return push_inst(compiler, INST_CODE_AND_DST(inst, inp_flags, reg) | A(tmp_reg) | IMM(argw));

#if (defined SLJIT_CONFIG_PPC_64 && SLJIT_CONFIG_PPC_64)
	}

	/* The rest is PPC-64 only. */

	FAIL_IF(load_immediate(compiler, tmp_reg, argw));

	inst = data_transfer_insts[(inp_flags | INDEXED) & MEM_MASK];
	return push_inst(compiler, INST_CODE_AND_DST(inst, inp_flags, reg) | A(arg) | B(tmp_reg));
#endif
}