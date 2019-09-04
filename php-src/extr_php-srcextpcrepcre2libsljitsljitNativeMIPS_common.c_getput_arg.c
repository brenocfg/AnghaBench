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
struct sljit_compiler {int cache_argw; size_t cache_arg; } ;
typedef  int sljit_sw ;
typedef  size_t sljit_s32 ;

/* Variables and functions */
 int ADDIU_W ; 
 int ADDU_W ; 
 int D (size_t) ; 
 int DA (size_t) ; 
 size_t DR (size_t) ; 
 int /*<<< orphan*/  FAIL_IF (size_t) ; 
 size_t GPR_REG ; 
 int IMM (int) ; 
 size_t LOAD_DATA ; 
 size_t MEM_MASK ; 
 size_t MOVABLE_INS ; 
 size_t OFFS_REG (size_t) ; 
 size_t OFFS_REG_MASK ; 
 size_t REG_MASK ; 
 int S (size_t) ; 
 int SA (size_t) ; 
 int SH_IMM (int) ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (size_t) ; 
 size_t SLJIT_MEM ; 
 scalar_t__ SLJIT_UNLIKELY (int) ; 
 int SLL_W ; 
 int T (size_t) ; 
 int TA (size_t) ; 
 size_t TMP_REG1 ; 
 size_t TMP_REG3 ; 
 int* data_transfer_insts ; 
 size_t load_immediate (struct sljit_compiler*,size_t,int) ; 
 size_t push_inst (struct sljit_compiler*,int,size_t) ; 

__attribute__((used)) static sljit_s32 getput_arg(struct sljit_compiler *compiler, sljit_s32 flags, sljit_s32 reg_ar, sljit_s32 arg, sljit_sw argw, sljit_s32 next_arg, sljit_sw next_argw)
{
	sljit_s32 tmp_ar, base, delay_slot;

	SLJIT_ASSERT(arg & SLJIT_MEM);
	if (!(next_arg & SLJIT_MEM)) {
		next_arg = 0;
		next_argw = 0;
	}

	if ((flags & MEM_MASK) <= GPR_REG && (flags & LOAD_DATA)) {
		tmp_ar = reg_ar;
		delay_slot = reg_ar;
	}
	else {
		tmp_ar = DR(TMP_REG1);
		delay_slot = MOVABLE_INS;
	}
	base = arg & REG_MASK;

	if (SLJIT_UNLIKELY(arg & OFFS_REG_MASK)) {
		argw &= 0x3;

		/* Using the cache. */
		if (argw == compiler->cache_argw) {
			if (arg == compiler->cache_arg)
				return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(TMP_REG3) | TA(reg_ar), delay_slot);

			if ((SLJIT_MEM | (arg & OFFS_REG_MASK)) == compiler->cache_arg) {
				if (arg == next_arg && argw == (next_argw & 0x3)) {
					compiler->cache_arg = arg;
					compiler->cache_argw = argw;
					FAIL_IF(push_inst(compiler, ADDU_W | S(base) | T(TMP_REG3) | D(TMP_REG3), DR(TMP_REG3)));
					return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(TMP_REG3) | TA(reg_ar), delay_slot);
				}
				FAIL_IF(push_inst(compiler, ADDU_W | S(base) | T(TMP_REG3) | DA(tmp_ar), tmp_ar));
				return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | SA(tmp_ar) | TA(reg_ar), delay_slot);
			}
		}

		if (SLJIT_UNLIKELY(argw)) {
			compiler->cache_arg = SLJIT_MEM | (arg & OFFS_REG_MASK);
			compiler->cache_argw = argw;
			FAIL_IF(push_inst(compiler, SLL_W | T(OFFS_REG(arg)) | D(TMP_REG3) | SH_IMM(argw), DR(TMP_REG3)));
		}

		if (arg == next_arg && argw == (next_argw & 0x3)) {
			compiler->cache_arg = arg;
			compiler->cache_argw = argw;
			FAIL_IF(push_inst(compiler, ADDU_W | S(base) | T(!argw ? OFFS_REG(arg) : TMP_REG3) | D(TMP_REG3), DR(TMP_REG3)));
			tmp_ar = DR(TMP_REG3);
		}
		else
			FAIL_IF(push_inst(compiler, ADDU_W | S(base) | T(!argw ? OFFS_REG(arg) : TMP_REG3) | DA(tmp_ar), tmp_ar));
		return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | SA(tmp_ar) | TA(reg_ar), delay_slot);
	}

	if (compiler->cache_arg == arg && argw - compiler->cache_argw <= SIMM_MAX && argw - compiler->cache_argw >= SIMM_MIN) {
		if (argw != compiler->cache_argw) {
			FAIL_IF(push_inst(compiler, ADDIU_W | S(TMP_REG3) | T(TMP_REG3) | IMM(argw - compiler->cache_argw), DR(TMP_REG3)));
			compiler->cache_argw = argw;
		}
		return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(TMP_REG3) | TA(reg_ar), delay_slot);
	}

	if (compiler->cache_arg == SLJIT_MEM && argw - compiler->cache_argw <= SIMM_MAX && argw - compiler->cache_argw >= SIMM_MIN) {
		if (argw != compiler->cache_argw)
			FAIL_IF(push_inst(compiler, ADDIU_W | S(TMP_REG3) | T(TMP_REG3) | IMM(argw - compiler->cache_argw), DR(TMP_REG3)));
	}
	else {
		compiler->cache_arg = SLJIT_MEM;
		FAIL_IF(load_immediate(compiler, DR(TMP_REG3), argw));
	}
	compiler->cache_argw = argw;

	if (!base)
		return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(TMP_REG3) | TA(reg_ar), delay_slot);

	if (arg == next_arg && next_argw - argw <= SIMM_MAX && next_argw - argw >= SIMM_MIN) {
		compiler->cache_arg = arg;
		FAIL_IF(push_inst(compiler, ADDU_W | S(TMP_REG3) | T(base) | D(TMP_REG3), DR(TMP_REG3)));
		return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | S(TMP_REG3) | TA(reg_ar), delay_slot);
	}

	FAIL_IF(push_inst(compiler, ADDU_W | S(TMP_REG3) | T(base) | DA(tmp_ar), tmp_ar));
	return push_inst(compiler, data_transfer_insts[flags & MEM_MASK] | SA(tmp_ar) | TA(reg_ar), delay_slot);
}