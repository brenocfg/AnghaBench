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
typedef  int sljit_uw ;
typedef  int sljit_sw ;
typedef  int sljit_s32 ;
typedef  int sljit_ins ;

/* Variables and functions */
 int ADDIU ; 
 int DA (int) ; 
 int DSLL ; 
 int DSLL32 ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int IMM (int) ; 
 int LUI ; 
 int ORI ; 
 int SA (int) ; 
 int SH_IMM (int) ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 int SLJIT_SUCCESS ; 
 int TA (int) ; 
 int push_inst (struct sljit_compiler*,int,int) ; 

__attribute__((used)) static sljit_s32 load_immediate(struct sljit_compiler *compiler, sljit_s32 dst_ar, sljit_sw imm)
{
	sljit_s32 shift = 32;
	sljit_s32 shift2;
	sljit_s32 inv = 0;
	sljit_ins ins;
	sljit_uw uimm;

	if (!(imm & ~0xffff))
		return push_inst(compiler, ORI | SA(0) | TA(dst_ar) | IMM(imm), dst_ar);

	if (imm < 0 && imm >= SIMM_MIN)
		return push_inst(compiler, ADDIU | SA(0) | TA(dst_ar) | IMM(imm), dst_ar);

	if (imm <= 0x7fffffffl && imm >= -0x80000000l) {
		FAIL_IF(push_inst(compiler, LUI | TA(dst_ar) | IMM(imm >> 16), dst_ar));
		return (imm & 0xffff) ? push_inst(compiler, ORI | SA(dst_ar) | TA(dst_ar) | IMM(imm), dst_ar) : SLJIT_SUCCESS;
	}

	/* Zero extended number. */
	uimm = imm;
	if (imm < 0) {
		uimm = ~imm;
		inv = 1;
	}

	while (!(uimm & 0xff00000000000000l)) {
		shift -= 8;
		uimm <<= 8;
	}

	if (!(uimm & 0xf000000000000000l)) {
		shift -= 4;
		uimm <<= 4;
	}

	if (!(uimm & 0xc000000000000000l)) {
		shift -= 2;
		uimm <<= 2;
	}

	if ((sljit_sw)uimm < 0) {
		uimm >>= 1;
		shift += 1;
	}
	SLJIT_ASSERT(((uimm & 0xc000000000000000l) == 0x4000000000000000l) && (shift > 0) && (shift <= 32));

	if (inv)
		uimm = ~uimm;

	FAIL_IF(push_inst(compiler, LUI | TA(dst_ar) | IMM(uimm >> 48), dst_ar));
	if (uimm & 0x0000ffff00000000l)
		FAIL_IF(push_inst(compiler, ORI | SA(dst_ar) | TA(dst_ar) | IMM(uimm >> 32), dst_ar));

	imm &= (1l << shift) - 1;
	if (!(imm & ~0xffff)) {
		ins = (shift == 32) ? DSLL32 : DSLL;
		if (shift < 32)
			ins |= SH_IMM(shift);
		FAIL_IF(push_inst(compiler, ins | TA(dst_ar) | DA(dst_ar), dst_ar));
		return !(imm & 0xffff) ? SLJIT_SUCCESS : push_inst(compiler, ORI | SA(dst_ar) | TA(dst_ar) | IMM(imm), dst_ar);
	}

	/* Double shifts needs to be performed. */
	uimm <<= 32;
	shift2 = shift - 16;

	while (!(uimm & 0xf000000000000000l)) {
		shift2 -= 4;
		uimm <<= 4;
	}

	if (!(uimm & 0xc000000000000000l)) {
		shift2 -= 2;
		uimm <<= 2;
	}

	if (!(uimm & 0x8000000000000000l)) {
		shift2--;
		uimm <<= 1;
	}

	SLJIT_ASSERT((uimm & 0x8000000000000000l) && (shift2 > 0) && (shift2 <= 16));

	FAIL_IF(push_inst(compiler, DSLL | TA(dst_ar) | DA(dst_ar) | SH_IMM(shift - shift2), dst_ar));
	FAIL_IF(push_inst(compiler, ORI | SA(dst_ar) | TA(dst_ar) | IMM(uimm >> 48), dst_ar));
	FAIL_IF(push_inst(compiler, DSLL | TA(dst_ar) | DA(dst_ar) | SH_IMM(shift2), dst_ar));

	imm &= (1l << shift2) - 1;
	return !(imm & 0xffff) ? SLJIT_SUCCESS : push_inst(compiler, ORI | SA(dst_ar) | TA(dst_ar) | IMM(imm), dst_ar);
}