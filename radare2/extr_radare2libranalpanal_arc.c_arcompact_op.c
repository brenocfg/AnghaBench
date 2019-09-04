#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_11__ {int opcode; int format; int a; int b; int c; int mode_n; int limm; int cond; int format2; int subopcode; int imm; int mode_zz; } ;
typedef  TYPE_1__ arc_fields ;
struct TYPE_13__ {scalar_t__ big_endian; } ;
struct TYPE_12__ {int ptr; int val; int refptr; int delay; int size; int nopcode; void* type; void* cond; void* fail; void* jump; } ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int ARC_REG_LIMM ; 
 int ARC_REG_PCL ; 
 void* R_ANAL_COND_EQ ; 
 void* R_ANAL_COND_NE ; 
 void* R_ANAL_OP_TYPE_ABS ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CCALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_CPL ; 
 void* R_ANAL_OP_TYPE_CRET ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_NOT ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_POP ; 
 void* R_ANAL_OP_TYPE_PUSH ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SAL ; 
 void* R_ANAL_OP_TYPE_SAR ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UCALL ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int SEX_S10 (int) ; 
 int SEX_S13 (int) ; 
 void* SEX_S21 (int) ; 
 void* SEX_S25 (int) ; 
 int SEX_S7 (int) ; 
 int SEX_S8 (int) ; 
 void* SEX_S9 (int) ; 
 void* UT64_MAX ; 
 int /*<<< orphan*/  arccompact_dump_fields (int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  arcompact_branch (TYPE_2__*,int,int,int) ; 
 int arcompact_genops (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  arcompact_jump (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* map_cond2radare (int) ; 
 int /*<<< orphan*/  map_zz2refptr (TYPE_2__*,int) ; 
 int r_read_be32 (int /*<<< orphan*/  const*) ; 
 int r_read_me32_arc (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int arcompact_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len) {
	ut32 words[2]; /* storage for the de-swizled opcode data */
	arc_fields fields;

	/* ARCompact ISA, including */
	/* ARCtangent-A5, ARC 600, ARC 700 */

	/* no unaligned code */
	if (addr % 2 != 0) {
		/* this fixes some of the reverse dissassembly issues */
		op->type = R_ANAL_OP_TYPE_ILL;
		return 0;
	}
	if (len < 8) {
		//when r_read_me32_arc/be32 oob read
		return 0;
	}

	op->type = R_ANAL_OP_TYPE_UNK;
	op->ptr = UT64_MAX;
	op->val = UT64_MAX;
	op->jump = UT64_MAX;
	op->fail = UT64_MAX;
	op->refptr = 0;
	op->delay = 0;

	if (anal->big_endian) {
		words[0] = r_read_be32 (&data[0]);
		words[1] = r_read_be32 (&data[4]);
	} else {
		words[0] = r_read_me32_arc (&data[0]);
		words[1] = r_read_me32_arc (&data[4]);
	}

	fields.opcode = (words[0] & 0xf8000000) >> 27;

	op->size = (fields.opcode >= 0x0c)? 2: 4;
	op->nopcode = op->size;
// eprintf ("%x\n", fields.opcode);

	switch (fields.opcode) {
	case 0:
		fields.format = (words[0] & 0x00010000) >> 16;
		fields.a = (words[0] & 0x07fe0000) >> 17;
		fields.b = (words[0] & 0x0000ffc0) >> 6;
		fields.c = (words[0] & 0x0000000f);
		fields.mode_n = (words[0] & 0x20) >> 5;
		fields.limm = fields.a << 1 | fields.b << 11;

		if (fields.format == 0) {
			/* Branch Conditionally 0x00 [0x0] */
			fields.limm = SEX_S21 (fields.limm);
			fields.cond = (words[0] & 0x1f);
			op->cond = map_cond2radare (fields.cond);
			op->type = R_ANAL_OP_TYPE_CJMP;
		} else {
			/* Branch Unconditional Far 0x00 [0x1] */
			fields.limm |= (fields.c & 0x0f) << 21;
			/* the  & 0xf clearly shows we dont overflow */
			/* TODO: dont generate code to show this */
			fields.limm = SEX_S25 (fields.limm);
			op->type = R_ANAL_OP_TYPE_JMP;
		}
		arcompact_branch (op, addr, fields.limm, fields.mode_n);
		break;
	case 1:
		fields.format = (words[0] & 0x00010000) >> 16;
		fields.mode_n = (words[0] & 0x20) >> 5;

		if (fields.format == 1) {
			fields.format2 = (words[0] & 0x10) >> 4;
			fields.subopcode = (words[0] & 0x0f);
			fields.b = (words[0] & 0x07000000) >> 24 | (words[0] & 0x7000) >> 9;
			fields.c = (words[0] & 0x00000fc0) >> 6;
			fields.imm = SEX_S9 ((words[0] & 0x00fe0000) >> 16 | (words[0] & 0x8000) >> 7);
			op->type = R_ANAL_OP_TYPE_CJMP;

			if (fields.format2 == 0) {
				/* Branch on Compare Register-Register, 0x01, [0x1, 0x0] */
				if (fields.b == ARC_REG_LIMM || fields.c == ARC_REG_LIMM) {
					op->size = 8;
					fields.limm = words[1];
				}
				/* TODO: cond codes (using the "br" mapping) */
			} else {
				/* Branch on Compare/Bit Test Register-Immediate, 0x01, [0x1, 0x1] */
				/* TODO: cond codes and imm u6 (using the "br" mapping) */
			}
			arcompact_branch (op, addr, fields.imm, fields.mode_n);
		} else {
			fields.format2 = (words[0] & 0x00020000) >> 17;
			fields.a = (words[0] & 0x07fc0000) >> 18;
			fields.b = (words[0] & 0x0000ffc0) >> 6;
			fields.c = (words[0] & 0x0000000f);
			fields.imm = fields.a << 2 | fields.b << 11;

			if (fields.format2 == 0) {
				/* Branch and Link Conditionally, 0x01, [0x0, 0x0] */
				fields.imm = SEX_S21 (fields.imm);
				fields.cond = (words[0] & 0x1f);
				op->cond = map_cond2radare (fields.cond);
				op->type = R_ANAL_OP_TYPE_CCALL;
			} else {
				/* Branch and Link Unconditional Far, 0x01, [0x0, 0x1] */
				fields.imm |= (fields.c & 0x0f) << 21;
				/* the  & 0xf clearly shows we dont overflow */
				/* TODO: dont generate code to show this */
				fields.imm = SEX_S25 (fields.imm);
				op->type = R_ANAL_OP_TYPE_CALL;
			}
			arcompact_branch (op, addr, fields.imm, fields.mode_n);
		}
		break;
	case 2: /* Load Register with Offset, 0x02 */
		fields.a = (words[0] & 0x0000003f);
		fields.b = (words[0] & 0x07000000) >> 24 | (words[0] & 0x7000) >> 9;
		fields.imm = SEX_S9 ((words[0] & 0x00ff0000) >> 16 | (words[0] & 0x8000) >> 7);
		/* fields.mode_aa = (words[0] & 0x600) >> 9; */
		fields.mode_zz = (words[0] & 0x180) >> 7;

		op->type = R_ANAL_OP_TYPE_LOAD;

		/* dst (fields.a) cannot be an extension core register */
		if (fields.a == ARC_REG_PCL || fields.a == 61 || (fields.a >= 0x20 && fields.a <= 0x2b)) {
			op->type = R_ANAL_OP_TYPE_ILL;
		}

		map_zz2refptr (op, fields.mode_zz);

		if (fields.b == ARC_REG_LIMM) {
			op->size = 8;
			fields.limm = words[1];
			op->ptr = fields.limm + fields.imm;
			/* fields.aa is reserved - and ignored with limm */
		} else if (fields.b == ARC_REG_PCL) { /* PCL */
			op->ptr = (addr & ~3) + fields.imm;
		}
		/* TODO: set op with GP,FP,SP src/dst details */
		break;
	case 3: /* Store Register with Offset, 0x03 */
		fields.c = (words[0] & 0xfc0) >> 6;
		fields.b = (words[0] & 0x07000000) >> 24 | (words[0] & 0x7000) >> 9;
		fields.imm = SEX_S9 ((words[0] & 0x00ff0000) >> 16 | (words[0] & 0x8000) >> 7);
		/* ut8 mode_aa = (words[0] & 0x18) >> 3; */
		fields.mode_zz = (words[0] & 0x6) >> 1;

		op->type = R_ANAL_OP_TYPE_STORE;

		map_zz2refptr (op, fields.mode_zz);

		if (fields.b == ARC_REG_LIMM) {
			op->size = 8;
			fields.limm = words[1];
			op->ptr = fields.limm;
		} else if (fields.c == ARC_REG_LIMM) {
			op->size = 8;
			fields.limm = words[1];
			op->val = fields.limm;
		}

		if (fields.b == ARC_REG_PCL) { /* PCL */
			op->ptr = (addr & ~3) + fields.imm;
		}
		/* TODO: set op with GP,FP,SP src/dst details */
		break;
	case 4: /* General Operations */
		op->type = R_ANAL_OP_TYPE_MOV;
		return arcompact_genops (op, addr, words);
	case 5:
	case 6:
	case 7:
	case 8: /* 32-bit Extension Instructions, 0x05 - 0x08 */
		fields.subopcode = (words[0] & 0x003f0000) >> 16;
		fields.format = (words[0] & 0x00c00000) >> 22;
		fields.c = (words[0] & 0x00000fc0) >> 6;
		fields.a = (words[0] & 0x0000003f);
		fields.b = (words[0] & 0x07000000) >> 24 | (words[0] & 0x7000) >> 9;

		if (fields.b == ARC_REG_LIMM) {
			op->size = 8;
			fields.limm = words[1];
		} else if ((fields.format == 0 || fields.format == 1) && (fields.a == ARC_REG_LIMM)) {
			op->size = 8;
			fields.limm = words[1];
		} else if ((fields.format == 0) && (fields.c == ARC_REG_LIMM)) {
			op->size = 8;
			fields.limm = words[1];
		} else if ((fields.format == 3) && ((fields.a & 0x20) == 0x20) && (fields.c == ARC_REG_LIMM)) {
			op->size = 8;
			fields.limm = words[1];
		}
		/* TODO: fill in the extansion functions */
		// op->type = R_ANAL_OP_TYPE_UNK;
		// op->type = R_ANAL_OP_TYPE_SHL;
		op->type = R_ANAL_OP_TYPE_SHR;
		break;
	case 0x09:
	case 0x0a:
	case 0x0b: /* Market Specific Extension Instructions, 0x09 - 0x0B */
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	case 0x0c: /* Load /Add Register-Register, 0x0C, [0x00 - 0x03] */
		op->type = R_ANAL_OP_TYPE_LOAD;
		fields.subopcode = (words[0] & 0x00180000) >> 19;
		/* fields.a	= (words[0] & 0x00070000) >> 16; */
		/* fields.c	= (words[0] & 0x00e00000) >> 21; */
		/* fields.b	= (words[0] & 0x07000000) >> 24; */

		switch (fields.subopcode) {
		case 0: /* Load long word (reg.+reg.) */
		case 1: /* Load unsigned byte (reg.+reg.) */
		case 2: /* Load unsigned word (reg.+reg.) */
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 3: /* Add */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		}
		break;
	case 0x0d: /* Add/Sub/Shift Register-Immediate, 0x0D, [0x00 - 0x03] */
		fields.subopcode = (words[0] & 0x00180000) >> 19;
		/* fields.imm = (words[0] & 0x00070000) >> 16; src2 u3 */
		/* fields.c = (words[0] & 0x00e00000) >> 21; dst */
		/* fields.b = (words[0] & 0x07000000) >> 24; src1 */

		switch (fields.subopcode) {
		case 0: /* Add */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 1: /* Subtract */
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case 2: /* Multiple arithmetic shift left */
			op->type = R_ANAL_OP_TYPE_SHL;
			break;
		case 3: /* Multiple arithmetic shift right */
			op->type = R_ANAL_OP_TYPE_SHR;
			break;
		}
		break;
	case 0x0e: /* Mov/Cmp/Add with High Register, 0x0E, [0x00 - 0x03] */
		fields.subopcode = (words[0] & 0x00180000) >> 19;
		/* fields.b	= (words[0] & 0x07000000) >> 24; dst, src1 */
		fields.c = (words[0] & 0x00e00000) >> 21 | (words[0] & 0x00070000) >> 13; /* src2 */

		if (fields.c == ARC_REG_LIMM) {
			op->size = 6;
			op->val = (words[0] & 0x0000ffff) << 16 | (words[1] & 0xffff0000) >> 16;
		}

		switch (fields.subopcode) {
		case 0: /* Add */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 1: /* Move */
		case 3: /* Move */
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 2: /* Compare */
			op->type = R_ANAL_OP_TYPE_CMP;
			break;
		}
		break;
	case 0xf: /* General Register Format Instructions, 0x0F, [0x00 - 0x1F] */
		fields.subopcode = (words[0] & 0x001f0000) >> 16;
		fields.c = (words[0] & 0x00e00000) >> (16 + 5);
		fields.b = (words[0] & 0x07000000) >> (16 + 8);

		switch (fields.subopcode) {
		case 0: /* Single Operand, Jumps and Special Format Instructions, 0x0F, [0x00, 0x00 - 0x07] */
			switch (fields.c) {
			case 0: /* J_S [r]*/
				op->type = R_ANAL_OP_TYPE_UJMP;
				arcompact_jump (op, 0, 0, 0);
				break;
			case 1: /* J_S.D [r] */
				op->type = R_ANAL_OP_TYPE_UJMP;
				arcompact_jump (op, 0, 0, 1);
				break;
			case 2: /* JL_S [r] */
				op->type = R_ANAL_OP_TYPE_UCALL;
				arcompact_jump (op, 0, 0, 0);
				break;
			case 3: /* JL_S.D [r] */
				op->type = R_ANAL_OP_TYPE_UCALL;
				arcompact_jump (op, 0, 0, 1);
				break;
			case 4:
			case 5: /* Reserved - instruction error */
				op->type = R_ANAL_OP_TYPE_ILL;
				break;
			case 6: /* SUB_S.NE [b] */
				op->cond = R_ANAL_COND_NE;
				op->type = R_ANAL_OP_TYPE_SUB;
				break;
			case 7: /* Zero Operand Instructions, 0x0F, [0x00, 0x07, 0x00 - 0x07] */
				switch (fields.b) {
				case 0: /* nop_s */
					op->type = R_ANAL_OP_TYPE_NOP;
					op->size = 4;
					break;
				case 1:
				case 2:
				case 3: /* unimplemented and Reserved - instruction error */
					op->type = R_ANAL_OP_TYPE_ILL;
					break;
				case 4: /* JEQ_S [blink] */
					op->cond = R_ANAL_COND_EQ;
					op->type = R_ANAL_OP_TYPE_CRET;
					break;
				case 5: /* JNE_S [blink] */
					op->cond = R_ANAL_COND_NE;
					op->type = R_ANAL_OP_TYPE_CRET;
					break;
				case 7: /* J_S.D [blink] */
					op->delay = 1;
				/* fall through */
				case 6: /* J_S [blink] */
					op->type = R_ANAL_OP_TYPE_RET;
					break;
				}
				break;
			}
			break;
		case 1:
		case 3:
		case 8:
		case 9:
		case 0xa:
		case 0x17: /* Reserved - instruction error */
			op->type = R_ANAL_OP_TYPE_ILL;
			break;
		case 2:
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case 4:
			op->type = R_ANAL_OP_TYPE_AND;
			break;
		case 5:
			op->type = R_ANAL_OP_TYPE_OR;
			break;
		case 6: /* Logical bitwise AND with invert */
			/* dest = src1 AND NOT src2 */
			op->type = R_ANAL_OP_TYPE_AND;
			break;
		case 7:
			op->type = R_ANAL_OP_TYPE_XOR;
			break;
		case 0xb: /* Test */
			/* no dst, b AND c */
			op->type = R_ANAL_OP_TYPE_AND;
			break;
		case 0xc:
			op->type = R_ANAL_OP_TYPE_MUL;
			break;
		case 0xd:  /* Sign extend byte */
		case 0xe:  /* Sign extend word */
		case 0xf:  /* Zero extend byte */
		case 0x10: /* Zero extend word */
		case 0x13: /* Negate */
			op->type = R_ANAL_OP_TYPE_CPL;
			break;
		case 0x11:
			op->type = R_ANAL_OP_TYPE_ABS;
			break;
		case 0x12:
			op->type = R_ANAL_OP_TYPE_NOT;
			break;
		case 0x14: /* Add with left shift by 1 */
		case 0x15: /* Add with left shift by 2 */
		case 0x16: /* Add with left shift by 3 */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 0x18: /* Multiple arithmetic shift left */
			op->type = R_ANAL_OP_TYPE_SAL;
			break;
		case 0x19: /* Multiple logical shift right */
			op->type = R_ANAL_OP_TYPE_SHR;
			break;
		case 0x1a: /* Multiple arithmetic shift right */
			op->type = R_ANAL_OP_TYPE_SAR;
			break;
		case 0x1b: /* Arithmetic shift left by one */
			op->type = R_ANAL_OP_TYPE_SAL;
			break;
		case 0x1c: /* Arithmetic shift right by one */
			op->type = R_ANAL_OP_TYPE_SAR;
			break;
		case 0x1d: /* Logical shift right by one */
			op->type = R_ANAL_OP_TYPE_SHL;
			break;
		case 0x1e:
			op->type = R_ANAL_OP_TYPE_TRAP;
			/* TODO: the description sounds more like a */
			/* R_ANAL_OP_TYPE_SWI, but I dont know what */
			/* difference that would make to radare */
			break;
		case 0x1f:
			op->type = R_ANAL_OP_TYPE_TRAP;
			/* TODO: this should be R_ANAL_OP_TYPE_DEBUG, */
			/* but that type is commented out */
			break;
		}
		break;
	case 0x10: /* LD_S	c,[b,u7] */
	case 0x11: /* LDB_S	c,[b,u5] */
	case 0x12: /* LDW_S	c,[b,u6] */
	case 0x13: /* LDW_S.X	c,[b,u6] */
		/* Load/Store with Offset, 0x10 - 0x16 */
		op->type = R_ANAL_OP_TYPE_LOAD;
		break;
	case 0x14: /* ST_S	c, [b, u7] */
	case 0x15: /* STB_S c, [b, u5] */
	case 0x16: /* STW_S c, [b, u6] */
		/* Load/Store with Offset, 0x10 - 0x16 */
		op->type = R_ANAL_OP_TYPE_STORE;
		break;
	case 0x17: /* Shift/Subtract/Bit Immediate, 0x17, [0x00 - 0x07] */
		fields.subopcode = (words[0] & 0x00e00000) >> (16 + 5);
		switch (fields.subopcode) {
		case 0: /* Multiple arithmetic shift left */
			op->type = R_ANAL_OP_TYPE_SAL;
			break;
		case 1: /* Multiple logical shift left */
			op->type = R_ANAL_OP_TYPE_SHL;
			break;
		case 2: /* Multiple arithmetic shift right */
			op->type = R_ANAL_OP_TYPE_SAR;
			break;
		case 3: /* Subtract */
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case 4: /* Bit set */
			op->type = R_ANAL_OP_TYPE_OR;
			break;
		case 5: /* Bit clear */
		case 6: /* Bit mask */
		case 7: /* Bit test */
			op->type = R_ANAL_OP_TYPE_AND;
			break;
		}
		break;
	case 0x18: /* Stack Pointer Based Instructions, 0x18, [0x00 - 0x07]	*/
		fields.subopcode = (words[0] & 0x00e00000) >> (16 + 5);
		switch (fields.subopcode) {
		case 0: /* Load long word sp-rel. */
		case 1: /* Load unsigned byte sp-rel. */
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 2: /* Store long word sp-rel. */
		case 3: /* Store unsigned byte sp-rel. */
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case 4: /* Add */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case 5: /* Add/Subtract SP Relative, 0x18, [0x05, 0x00-0x07] */
			fields.b = (words[0] & 0x07000000) >> (16 + 8);
			switch (fields.b) {
			case 0: /* Add immediate to SP */
				op->type = R_ANAL_OP_TYPE_ADD;
				break;
			case 1: /* Subtract immediate from SP */
				op->type = R_ANAL_OP_TYPE_SUB;
				break;
			default:
				op->type = R_ANAL_OP_TYPE_ILL;
				break;
			}
			break;
		case 6: /* POP Register from Stack, 0x18, [0x06, 0x00-0x1F] */
			fields.c = (words[0] & 0x001f0000) >> 16;
			switch (fields.c) {
			case 1:    /* Pop register from stack */
			case 0x11: /* Pop blink from stack */
				op->type = R_ANAL_OP_TYPE_POP;
				break;
			default:
				op->type = R_ANAL_OP_TYPE_ILL;
				break;
			}
			break;
		case 7: /* PUSH Register to Stack, 0x18, [0x07, 0x00-0x1F] */
			fields.c = (words[0] & 0x001f0000) >> 16;
			switch (fields.c) {
			case 1:    /* Push register to stack */
			case 0x11: /* Push blink to stack */
				op->type = R_ANAL_OP_TYPE_PUSH;
				break;
			default:
				op->type = R_ANAL_OP_TYPE_ILL;
				break;
			}
			break;
		}
		break;
	case 0x19: /* Load/Add GP-Relative, 0x19, [0x00 - 0x03] */
		fields.subopcode = (words[0] & 0x06000000) >> (16 + 9);
		switch (fields.subopcode) {
		case 0: /* Load gp-relative (32-bit aligned) to r0 */
		case 1: /* Load unsigned byte gp-relative (8-bit aligned) to r0 */
		case 2: /* Load unsigned word gp-relative (16-bit aligned) to r0 */
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 3: /* Add gp-relative (32-bit aligned) to r0 */
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		}
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	case 0x1a: /* Load PCL-Relative, 0x1A */
		fields.c = (words[0] & 0x00ff0000) >> 14;
		op->ptr = (addr & ~3) + fields.c;
		op->refptr = 4;
		op->type = R_ANAL_OP_TYPE_LOAD;
		break;
	case 0x1b: /* Move Immediate, 0x1B */
		op->val = (words[0] & 0x00ff0000) >> 16;
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 0x1c: /* ADD/CMP Immediate, 0x1C, [0x00 - 0x01] */
		fields.subopcode = (words[0] & 0x00800000) >> (16 + 7);
		if (fields.subopcode == 0) {
			op->type = R_ANAL_OP_TYPE_ADD;
		} else {
			op->type = R_ANAL_OP_TYPE_CMP;
		}
		break;
	case 0x1d: /* Branch on Compare Register with Zero, 0x1D, [0x00 - 0x01] */
		/* fields.subopcode = (words[0] & 0x00800000) >> (16+7); */
		fields.imm = SEX_S8 ((words[0] & 0x007f0000) >> (16 - 1));
		/* fields.subopcode? reg NE: reg EQ; */
		op->type = R_ANAL_OP_TYPE_CJMP;
		arcompact_branch (op, addr, fields.imm, 0);
		break;
	case 0x1e: /* Branch Conditionally, 0x1E, [0x00 - 0x03] */
		fields.subopcode = (words[0] & 0x06000000) >> (16 + 9);
		fields.imm = SEX_S10 ((words[0] & 0x01ff0000) >> (16 - 1));
		switch (fields.subopcode) {
		case 0: /* B_S */
			op->type = R_ANAL_OP_TYPE_JMP;
			break;
		case 1: /* BEQ_S */
			op->cond = R_ANAL_COND_EQ;
			op->type = R_ANAL_OP_TYPE_CJMP;
			break;
		case 2: /* BNE_S */
			op->cond = R_ANAL_COND_NE;
			op->type = R_ANAL_OP_TYPE_CJMP;
			break;
		case 3: /* Bcc_S */
			op->type = R_ANAL_OP_TYPE_CJMP;
			fields.imm = SEX_S7 ((words[0] & 0x003f0000) >> (16 - 1));
			/* TODO: cond codes (looks like it is the BR table again?) */
			break;
		}
		arcompact_branch (op, addr, fields.imm, 0);
		break;
	case 0x1f: /* Branch and Link Unconditionally, 0x1F */
		fields.imm = SEX_S13 ((words[0] & 0x07ff0000) >> (16 - 2));
		op->type = R_ANAL_OP_TYPE_CALL;
		arcompact_branch (op, addr, fields.imm, 0);
		break;
	}
	arccompact_dump_fields (addr, words, &fields);
	return op->size;
}