#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  long long ut64 ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_20__ {int id; long long const size; TYPE_4__* detail; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_6__ cs_insn ;
struct TYPE_22__ {int bits; } ;
struct TYPE_19__ {int new_bits; } ;
struct TYPE_21__ {long long addr; scalar_t__ cond; int cycles; int ptrsize; int ptr; long long jump; long long fail; long long stackptr; long long val; long long const size; int refptr; int eob; void* type; TYPE_5__ hint; void* family; void* ireg; void* stackop; void* reg; } ;
struct TYPE_17__ {int op_count; int /*<<< orphan*/  cc; TYPE_1__* operands; } ;
struct TYPE_18__ {TYPE_3__ arm; } ;
struct TYPE_16__ {int /*<<< orphan*/  index; } ;
struct TYPE_15__ {int reg; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_2__ mem; int /*<<< orphan*/  reg; } ;
typedef  TYPE_7__ RAnalOp ;
typedef  TYPE_8__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CC_AL ; 
 int /*<<< orphan*/  ARM_CC_INVALID ; 
 int /*<<< orphan*/  ARM_GRP_CRC ; 
 int /*<<< orphan*/  ARM_GRP_CRYPTO ; 
 int /*<<< orphan*/  ARM_GRP_FPARMV8 ; 
 int /*<<< orphan*/  ARM_GRP_NEON ; 
 int /*<<< orphan*/  ARM_GRP_THUMB2DSP ; 
#define  ARM_INS_ADD 224 
#define  ARM_INS_ADDW 223 
#define  ARM_INS_ADR 222 
#define  ARM_INS_AND 221 
#define  ARM_INS_ASR 220 
#define  ARM_INS_B 219 
#define  ARM_INS_BFI 218 
#define  ARM_INS_BIC 217 
#define  ARM_INS_BL 216 
#define  ARM_INS_BLX 215 
#define  ARM_INS_BX 214 
#define  ARM_INS_BXJ 213 
#define  ARM_INS_CBNZ 212 
#define  ARM_INS_CBZ 211 
#define  ARM_INS_CMN 210 
#define  ARM_INS_CMP 209 
#define  ARM_INS_EOR 208 
#define  ARM_INS_FLDMDBX 207 
#define  ARM_INS_FLDMIAX 206 
#define  ARM_INS_IT 205 
#define  ARM_INS_LDM 204 
#define  ARM_INS_LDMDA 203 
#define  ARM_INS_LDMDB 202 
#define  ARM_INS_LDMIB 201 
#define  ARM_INS_LDR 200 
#define  ARM_INS_LDRB 199 
#define  ARM_INS_LDRBT 198 
#define  ARM_INS_LDRD 197 
#define  ARM_INS_LDREX 196 
#define  ARM_INS_LDREXB 195 
#define  ARM_INS_LDREXD 194 
#define  ARM_INS_LDREXH 193 
#define  ARM_INS_LDRH 192 
#define  ARM_INS_LDRHT 191 
#define  ARM_INS_LDRSB 190 
#define  ARM_INS_LDRSBT 189 
#define  ARM_INS_LDRSH 188 
#define  ARM_INS_LDRSHT 187 
#define  ARM_INS_LDRT 186 
#define  ARM_INS_LSL 185 
#define  ARM_INS_LSR 184 
#define  ARM_INS_MOV 183 
#define  ARM_INS_MOVT 182 
#define  ARM_INS_MOVW 181 
#define  ARM_INS_MRS 180 
#define  ARM_INS_MSR 179 
#define  ARM_INS_MUL 178 
#define  ARM_INS_NOP 177 
#define  ARM_INS_ORN 176 
#define  ARM_INS_ORR 175 
#define  ARM_INS_PLD 174 
#define  ARM_INS_POP 173 
#define  ARM_INS_PUSH 172 
#define  ARM_INS_ROR 171 
#define  ARM_INS_RRX 170 
#define  ARM_INS_SADD16 169 
#define  ARM_INS_SADD8 168 
#define  ARM_INS_SBFX 167 
#define  ARM_INS_SDIV 166 
#define  ARM_INS_SMULL 165 
#define  ARM_INS_SSUB16 164 
#define  ARM_INS_SSUB8 163 
#define  ARM_INS_STM 162 
#define  ARM_INS_STMDB 161 
#define  ARM_INS_STR 160 
#define  ARM_INS_STRB 159 
#define  ARM_INS_STRBT 158 
#define  ARM_INS_STRD 157 
#define  ARM_INS_STREX 156 
#define  ARM_INS_STREXB 155 
#define  ARM_INS_STREXD 154 
#define  ARM_INS_STREXH 153 
#define  ARM_INS_STRH 152 
#define  ARM_INS_STRHT 151 
#define  ARM_INS_STRT 150 
#define  ARM_INS_SUB 149 
#define  ARM_INS_SUBW 148 
#define  ARM_INS_SVC 147 
#define  ARM_INS_TBB 146 
#define  ARM_INS_TBH 145 
#define  ARM_INS_TRAP 144 
#define  ARM_INS_TST 143 
#define  ARM_INS_UBFX 142 
#define  ARM_INS_UDF 141 
#define  ARM_INS_UDIV 140 
#define  ARM_INS_UMULL 139 
#define  ARM_INS_VCMP 138 
#define  ARM_INS_VDIV 137 
#define  ARM_INS_VMOV 136 
#define  ARM_INS_VMOVL 135 
#define  ARM_INS_VMOVN 134 
#define  ARM_INS_VMUL 133 
#define  ARM_INS_VQMOVN 132 
#define  ARM_INS_VQMOVUN 131 
 int /*<<< orphan*/  ARM_OP_REG ; 
 int ARM_REG_FP ; 
#define  ARM_REG_IP 130 
#define  ARM_REG_LR 129 
#define  ARM_REG_PC 128 
 int ARM_REG_SP ; 
 long long const IMM (int) ; 
 TYPE_13__ INSOP (int) ; 
 int /*<<< orphan*/  ISIMM (int) ; 
 int /*<<< orphan*/  ISMEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISREG (int) ; 
 int MEMDISP (int) ; 
 int REGBASE (int) ; 
 int REGID (int) ; 
 scalar_t__ R_ANAL_COND_NV ; 
 void* R_ANAL_OP_FAMILY_CPU ; 
 void* R_ANAL_OP_FAMILY_CRYPTO ; 
 void* R_ANAL_OP_FAMILY_FPU ; 
 void* R_ANAL_OP_FAMILY_MMX ; 
 void* R_ANAL_OP_FAMILY_PRIV ; 
 void* R_ANAL_OP_FAMILY_THREAD ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_CRET ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LEA ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_POP ; 
 void* R_ANAL_OP_TYPE_PUSH ; 
 void* R_ANAL_OP_TYPE_RCALL ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_ROR ; 
 void* R_ANAL_OP_TYPE_SAR ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UCJMP ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 void* R_ANAL_STACK_GET ; 
 void* R_ANAL_STACK_INC ; 
 void* R_ANAL_STACK_SET ; 
 long long const UT32_MAX ; 
 int UT64_MAX ; 
 scalar_t__ cond_cs2r2 (int /*<<< orphan*/ ) ; 
 scalar_t__ cs_insn_group (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long lookahead (int /*<<< orphan*/ ,long long const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 void* r_str_get (int /*<<< orphan*/ ) ; 
 int r_str_nlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void anop32(RAnal *a, csh handle, RAnalOp *op, cs_insn *insn, bool thumb, const ut8 *buf, int len) {
	const ut64 addr = op->addr;
	const int pcdelta = thumb? 4 : 8;
	int i;
	op->cond = cond_cs2r2 (insn->detail->arm.cc);
	if (op->cond == R_ANAL_COND_NV) {
		op->type = R_ANAL_OP_TYPE_NOP;
		return;
	}
	op->cycles = 1;
	/* grab family */
	if (cs_insn_group (handle, insn, ARM_GRP_CRYPTO)) {
		op->family = R_ANAL_OP_FAMILY_CRYPTO;
	} else if (cs_insn_group (handle, insn, ARM_GRP_CRC)) {
		op->family = R_ANAL_OP_FAMILY_CRYPTO;
#if CS_API_MAJOR >= 4
	} else if (cs_insn_group (handle, insn, ARM_GRP_PRIVILEGE)) {
		op->family = R_ANAL_OP_FAMILY_PRIV;
	} else if (cs_insn_group (handle, insn, ARM_GRP_VIRTUALIZATION)) {
		op->family = R_ANAL_OP_FAMILY_VIRT;
#endif
	} else if (cs_insn_group (handle, insn, ARM_GRP_NEON)) {
		op->family = R_ANAL_OP_FAMILY_MMX;
	} else if (cs_insn_group (handle, insn, ARM_GRP_FPARMV8)) {
		op->family = R_ANAL_OP_FAMILY_FPU;
	} else if (cs_insn_group (handle, insn, ARM_GRP_THUMB2DSP)) {
		op->family = R_ANAL_OP_FAMILY_MMX;
	} else {
		op->family = R_ANAL_OP_FAMILY_CPU;
	}
	switch (insn->id) {
#if 0

If PC is specified for Rn, the value used is the address of the instruction plus 4.

These instructions cause a PC-relative forward branch using a table of single byte offsets (TBB) or halfword offsets (TBH). Rn provides a pointer to the table, and Rm supplies an index into the table. The branch length is twice the value of the byte (TBB) or the halfword (TBH) returned from the table. The target of the branch table must be in the same execution state.

jmp $$ + 4 + ( [delta] * 2 )

#endif
	case ARM_INS_TBH: // half word table
		op->type = R_ANAL_OP_TYPE_UJMP;
		op->cycles = 2;
		op->ptrsize = 2;
		op->ireg = r_str_get (cs_reg_name (handle, INSOP (0).mem.index));
		break;
	case ARM_INS_TBB: // byte jump table
		op->type = R_ANAL_OP_TYPE_UJMP;
		op->cycles = 2;
		op->ptrsize = 1;
		op->ireg = r_str_get (cs_reg_name (handle, INSOP (0).mem.index));
		break;
	case ARM_INS_PLD:
		op->type = R_ANAL_OP_TYPE_LEA; // not really a lea, just a prefetch
		if (ISMEM (0)) {
			int regBase = REGBASE(0);
			int delta = MEMDISP(0);
			if (regBase == ARM_REG_PC) {
				op->ptr = addr + 4 + delta;
			} else {
				// exotic pld
			}
		}
		break;
	case ARM_INS_IT:
	{
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = addr + insn->size;
		int distance = r_str_nlen (insn->mnemonic, 5);
		op->cycles = 2;
		op->fail = lookahead (handle, addr + insn->size, buf + insn->size, len - insn->size, distance);
		break;
	}
	case ARM_INS_NOP:
		op->type = R_ANAL_OP_TYPE_NOP;
		op->cycles = 1;
		break;
	case ARM_INS_POP:
	case ARM_INS_FLDMDBX:
	case ARM_INS_FLDMIAX:
	case ARM_INS_LDMDA:
	case ARM_INS_LDMDB:
	case ARM_INS_LDMIB:
	case ARM_INS_LDM:
		op->type = R_ANAL_OP_TYPE_POP;
		op->cycles = 2;
		for (i = 0; i < insn->detail->arm.op_count; i++) {
			if (insn->detail->arm.operands[i].type == ARM_OP_REG &&
					insn->detail->arm.operands[i].reg == ARM_REG_PC) {
				if (insn->detail->arm.cc == ARM_CC_AL) {
					op->type = R_ANAL_OP_TYPE_RET;
				} else {
					op->type = R_ANAL_OP_TYPE_CRET;
				}
				break;
			}
		}
		break;
	case ARM_INS_SUB:
		if (ISREG(0) && REGID(0) == ARM_REG_SP) {
				op->stackop = R_ANAL_STACK_INC;
				if (ISIMM(1)) {
					//0x0000bf4e      95b0           sub sp, 0x54
					op->stackptr = IMM (1);
				} else if ( ISIMM(2) && ISREG(1) && REGID(1) == ARM_REG_SP) {
					// 0x00008254    10d04de2     sub sp, sp, 0x10
					op->stackptr = IMM (2);
				}
				op->val = op->stackptr;
		}
		op->cycles = 1;
		/* fall-thru */
	case ARM_INS_SUBW:
	case ARM_INS_SSUB8:
	case ARM_INS_SSUB16:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case ARM_INS_ADD:
		op->type = R_ANAL_OP_TYPE_ADD;
		if (REGID(0) == ARM_REG_PC) {
			op->type = R_ANAL_OP_TYPE_UJMP;
			if (REGID(1) == ARM_REG_PC && insn->detail->arm.cc != ARM_CC_AL) {
				//op->type = R_ANAL_OP_TYPE_RCJMP;
				op->type = R_ANAL_OP_TYPE_UCJMP;
				op->fail = addr+op->size;
				op->jump = ((addr & ~3LL) + (thumb? 4: 8) + MEMDISP(1)) & UT64_MAX;
				op->ptr = (addr & ~3LL) + (thumb? 4: 8) + MEMDISP(1);
				op->refptr = 4;
				op->reg = r_str_get (cs_reg_name (handle, INSOP (2).reg));
				break;
			}
		}
		op->cycles = 1;
		break;
		/* fall-thru */
	case ARM_INS_ADDW:
	case ARM_INS_SADD8:
	case ARM_INS_SADD16:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case ARM_INS_SDIV:
	case ARM_INS_UDIV:
		op->cycles = 4;
		/* fall-thru */
	case ARM_INS_VDIV:
		op->type = R_ANAL_OP_TYPE_DIV;
		break;
	case ARM_INS_MUL:
	case ARM_INS_SMULL:
	case ARM_INS_UMULL:
		/* TODO: if next instruction is also a MUL, cycles are /=2 */
		/* also known as Register Indexing Addressing */
		op->cycles = 4;
		/* fall-thru */
	case ARM_INS_VMUL:
		op->type = R_ANAL_OP_TYPE_MUL;
		break;
	case ARM_INS_TRAP:
		op->type = R_ANAL_OP_TYPE_TRAP;
		op->cycles = 2;
		break;
	case ARM_INS_MOV:
		if (REGID(0) == ARM_REG_PC) {
			if (REGID(1) == ARM_REG_LR) {
				op->type = R_ANAL_OP_TYPE_RET;
			} else {
				op->type = R_ANAL_OP_TYPE_UJMP;
			}
		}
		if (ISIMM (1)) {
			op->val = IMM(1);
		}
		/* fall-thru */
	case ARM_INS_MOVT:
	case ARM_INS_MOVW:
	case ARM_INS_VMOVL:
	case ARM_INS_VMOVN:
	case ARM_INS_VQMOVUN:
	case ARM_INS_VQMOVN:
	case ARM_INS_SBFX:
	case ARM_INS_UBFX:
	case ARM_INS_BIC:
	case ARM_INS_BFI:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case ARM_INS_VMOV:
		op->type = R_ANAL_OP_TYPE_MOV;
		op->family = R_ANAL_OP_FAMILY_FPU;
		break;
	case ARM_INS_UDF:
		op->type = R_ANAL_OP_TYPE_TRAP;
		break;
	case ARM_INS_SVC:
		op->type = R_ANAL_OP_TYPE_SWI;
		op->val = IMM(0);
		break;
	case ARM_INS_ROR:
	case ARM_INS_RRX:
		op->cycles = 1;
		op->type = R_ANAL_OP_TYPE_ROR;
		break;
	case ARM_INS_AND:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case ARM_INS_ORR:
	case ARM_INS_ORN:
		op->type = R_ANAL_OP_TYPE_OR;
		break;
	case ARM_INS_EOR:
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case ARM_INS_CMP:
	case ARM_INS_CMN:
	case ARM_INS_TST:
		if (ISIMM(1)) {
			op->ptr = IMM(1);
		}
		op->reg = r_str_get (cs_reg_name (handle, INSOP (0).reg));
		/* fall-thru */
	case ARM_INS_VCMP:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case ARM_INS_LSL:
		op->cycles = 1;
		op->type = R_ANAL_OP_TYPE_SHL;
		break;
	case ARM_INS_LSR:
		op->cycles = 1;
		op->type = R_ANAL_OP_TYPE_SHR;
		break;
	case ARM_INS_ASR:
		op->cycles = 1;
		op->type = R_ANAL_OP_TYPE_SAR;
		break;
	case ARM_INS_PUSH:
	case ARM_INS_STM:
	case ARM_INS_STMDB:
		op->type = R_ANAL_OP_TYPE_PUSH;
// 0x00008160    04202de5     str r2, [sp, -4]!
// 0x000082a0    28000be5     str r0, [fp, -0x28]
		if (REGBASE(1) == ARM_REG_FP) {
			op->stackop = R_ANAL_STACK_SET;
			op->stackptr = 0;
			op->ptr = MEMDISP(1);
		}
		break;
	case ARM_INS_STREX:
	case ARM_INS_STREXB:
	case ARM_INS_STREXD:
	case ARM_INS_STREXH:
		op->family = R_ANAL_OP_FAMILY_THREAD;
		/* fall-thru */
	case ARM_INS_STR:
	case ARM_INS_STRB:
	case ARM_INS_STRD:
	case ARM_INS_STRBT:
	case ARM_INS_STRH:
	case ARM_INS_STRHT:
	case ARM_INS_STRT:
		op->cycles = 4;
		op->type = R_ANAL_OP_TYPE_STORE;
		if (REGBASE(1) == ARM_REG_FP) {
			op->stackop = R_ANAL_STACK_SET;
			op->stackptr = 0;
			op->ptr = -MEMDISP(1);
		}
		break;
	case ARM_INS_LDREX:
	case ARM_INS_LDREXB:
	case ARM_INS_LDREXD:
	case ARM_INS_LDREXH:
		op->family = R_ANAL_OP_FAMILY_THREAD;
		/* fall-thru */
	case ARM_INS_LDR:
	case ARM_INS_LDRD:
	case ARM_INS_LDRB:
	case ARM_INS_LDRBT:
	case ARM_INS_LDRH:
	case ARM_INS_LDRHT:
	case ARM_INS_LDRSB:
	case ARM_INS_LDRSBT:
	case ARM_INS_LDRSH:
	case ARM_INS_LDRSHT:
	case ARM_INS_LDRT:
		op->cycles = 4;
// 0x000082a8    28301be5     ldr r3, [fp, -0x28]
		if (REGID(0) == ARM_REG_PC) {
			op->type = R_ANAL_OP_TYPE_UJMP;
			if (insn->detail->arm.cc != ARM_CC_AL) {
				//op->type = R_ANAL_OP_TYPE_MCJMP;
				op->type = R_ANAL_OP_TYPE_UCJMP;
			}
		} else {
			op->type = R_ANAL_OP_TYPE_LOAD;
		}
		switch (insn->id) {
		case ARM_INS_LDRB:
			op->ptrsize = 1;
			break;
		case ARM_INS_LDRH:
		case ARM_INS_LDRHT:
			op->ptrsize = 2;
			break;
		}
		if (REGBASE(1) == ARM_REG_FP) {
			op->stackop = R_ANAL_STACK_GET;
			op->stackptr = 0;
			op->ptr = -MEMDISP(1);
		} else if (REGBASE(1) == ARM_REG_PC) {
			op->ptr = (addr & ~3LL) + (thumb? 4: 8) + MEMDISP(1);
			op->refptr = 4;
			if (REGID(0) == ARM_REG_PC && insn->detail->arm.cc != ARM_CC_AL) {
				//op->type = R_ANAL_OP_TYPE_MCJMP;
				op->type = R_ANAL_OP_TYPE_UCJMP;
				op->fail = addr+op->size;
				op->jump = ((addr & ~3LL) + (thumb? 4: 8) + MEMDISP(1)) & UT64_MAX;
				op->ireg = r_str_get (cs_reg_name (handle, INSOP (1).mem.index));
				break;
			}
		}
		break;
	case ARM_INS_MRS:
	case ARM_INS_MSR:
		op->type = R_ANAL_OP_TYPE_MOV;
		op->family = R_ANAL_OP_FAMILY_PRIV;
		break;
	case ARM_INS_BLX:
		op->cycles = 4;
		if (ISREG(0)) {
			/* blx reg */
			op->type = R_ANAL_OP_TYPE_RCALL;
		} else {
			/* blx label */
			op->type = R_ANAL_OP_TYPE_CALL;
			op->jump = IMM(0) & UT32_MAX;
			op->fail = addr + op->size;
			op->hint.new_bits = (a->bits == 32)? 16 : 32;
			//switch instruction set always with blx label
			// r_anal_hint_set_bits (a, op->jump, a->bits == 32? 16 : 32);
		}
		break;
	case ARM_INS_BL:
		/* bl label */
		op->cycles = 4;
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = IMM(0) & UT32_MAX;
		op->fail = addr + op->size;
		op->hint.new_bits = a->bits;
		break;
	case ARM_INS_CBZ:
	case ARM_INS_CBNZ:
		op->cycles = 4;
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = IMM(1) & UT32_MAX;
		op->fail = addr + op->size;
		if (op->jump == op->fail) {
			op->type = R_ANAL_OP_TYPE_JMP;
			op->fail = UT64_MAX;
		}
		break;
	case ARM_INS_B:
		/* b.cc label */
		op->cycles = 4;
		if (insn->detail->arm.cc == ARM_CC_INVALID) {
			op->type = R_ANAL_OP_TYPE_ILL;
			op->fail = addr+op->size;
		} else if (insn->detail->arm.cc == ARM_CC_AL) {
			op->type = R_ANAL_OP_TYPE_JMP;
			op->fail = UT64_MAX;
		} else {
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr+op->size;
		}
		op->jump = IMM(0) & UT32_MAX;
		// propagate bits to create correctly hints ranges
		op->hint.new_bits = a->bits;
		break;
	case ARM_INS_BX:
	case ARM_INS_BXJ:
		/* bx reg */
		op->cycles = 4;
		switch (REGID(0)) {
		case ARM_REG_LR:
			op->type = R_ANAL_OP_TYPE_RET;
			break;
		case ARM_REG_IP:
			op->type = R_ANAL_OP_TYPE_UJMP;
			break;
		case ARM_REG_PC:
			// bx pc is well known without ESIL
			op->type = R_ANAL_OP_TYPE_UJMP;
			op->jump = (addr & ~3LL) + pcdelta;
			op->hint.new_bits = 32;
			break;
		default:
			op->type = R_ANAL_OP_TYPE_UJMP;
			op->eob = true;
			break;
		}
		break;
	case ARM_INS_ADR:
		op->cycles = 2;
		op->type = R_ANAL_OP_TYPE_LEA;
		// Set the pointer address and align it
		op->ptr = IMM(1) + addr + 4 - (addr%4);
		op->refptr = 1;
		break;
	default:
		break;
	}
}