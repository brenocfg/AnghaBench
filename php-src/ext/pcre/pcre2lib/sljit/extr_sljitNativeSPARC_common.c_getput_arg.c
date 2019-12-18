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
struct sljit_compiler {size_t cache_arg; int cache_argw; } ;
typedef  int sljit_sw ;
typedef  size_t sljit_s32 ;
typedef  int sljit_ins ;

/* Variables and functions */
 int ADD ; 
 int D (size_t) ; 
 size_t DR (size_t) ; 
 int /*<<< orphan*/  FAIL_IF (size_t) ; 
 int FD (size_t) ; 
 size_t GPR_REG ; 
 int IMM (int /*<<< orphan*/ ) ; 
 int IMM_ARG ; 
 size_t LOAD_DATA ; 
 size_t MEM_MASK ; 
 size_t MOVABLE_INS ; 
 size_t OFFS_REG (size_t) ; 
 size_t OFFS_REG_MASK ; 
 size_t REG_MASK ; 
 int S1 (size_t) ; 
 int S2 (size_t) ; 
 scalar_t__ SIMM_MAX ; 
 scalar_t__ SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (size_t) ; 
 size_t SLJIT_MEM ; 
 scalar_t__ SLJIT_UNLIKELY (size_t) ; 
 int SLL_W ; 
 size_t TMP_REG1 ; 
 size_t TMP_REG3 ; 
 int* data_transfer_insts ; 
 size_t load_immediate (struct sljit_compiler*,size_t,int) ; 
 size_t push_inst (struct sljit_compiler*,int,size_t) ; 

__attribute__((used)) static sljit_s32 getput_arg(struct sljit_compiler *compiler, sljit_s32 flags, sljit_s32 reg, sljit_s32 arg, sljit_sw argw, sljit_s32 next_arg, sljit_sw next_argw)
{
	sljit_s32 base, arg2, delay_slot;
	sljit_ins dest;

	SLJIT_ASSERT(arg & SLJIT_MEM);
	if (!(next_arg & SLJIT_MEM)) {
		next_arg = 0;
		next_argw = 0;
	}

	base = arg & REG_MASK;
	if (SLJIT_UNLIKELY(arg & OFFS_REG_MASK)) {
		argw &= 0x3;

		/* Using the cache. */
		if (((SLJIT_MEM | (arg & OFFS_REG_MASK)) == compiler->cache_arg) && (argw == compiler->cache_argw))
			arg2 = TMP_REG3;
		else {
			if ((arg & OFFS_REG_MASK) == (next_arg & OFFS_REG_MASK) && argw == (next_argw & 0x3)) {
				compiler->cache_arg = SLJIT_MEM | (arg & OFFS_REG_MASK);
				compiler->cache_argw = argw;
				arg2 = TMP_REG3;
			}
			else if ((flags & LOAD_DATA) && ((flags & MEM_MASK) <= GPR_REG) && reg != base && reg != OFFS_REG(arg))
				arg2 = reg;
			else /* It must be a mov operation, so tmp1 must be free to use. */
				arg2 = TMP_REG1;
			FAIL_IF(push_inst(compiler, SLL_W | D(arg2) | S1(OFFS_REG(arg)) | IMM_ARG | argw, DR(arg2)));
		}
	}
	else {
		/* Using the cache. */
		if ((compiler->cache_arg == SLJIT_MEM) && (argw - compiler->cache_argw) <= SIMM_MAX && (argw - compiler->cache_argw) >= SIMM_MIN) {
			if (argw != compiler->cache_argw) {
				FAIL_IF(push_inst(compiler, ADD | D(TMP_REG3) | S1(TMP_REG3) | IMM(argw - compiler->cache_argw), DR(TMP_REG3)));
				compiler->cache_argw = argw;
			}
			arg2 = TMP_REG3;
		} else {
			if ((next_argw - argw) <= SIMM_MAX && (next_argw - argw) >= SIMM_MIN) {
				compiler->cache_arg = SLJIT_MEM;
				compiler->cache_argw = argw;
				arg2 = TMP_REG3;
			}
			else if ((flags & LOAD_DATA) && ((flags & MEM_MASK) <= GPR_REG) && reg != base)
				arg2 = reg;
			else /* It must be a mov operation, so tmp1 must be free to use. */
				arg2 = TMP_REG1;
			FAIL_IF(load_immediate(compiler, arg2, argw));
		}
	}

	dest = ((flags & MEM_MASK) <= GPR_REG ? D(reg) : FD(reg));
	delay_slot = ((flags & MEM_MASK) <= GPR_REG && (flags & LOAD_DATA)) ? DR(reg) : MOVABLE_INS;
	if (!base)
		return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | dest | S1(arg2) | IMM(0), delay_slot);
	return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | dest | S1(base) | S2(arg2), delay_slot);
}