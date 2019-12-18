#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_7__ {int format; int subopcode; int c; int a; int b; int mode_n; int limm; int imm; int cond; int mode_m; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ arc_fields ;
struct TYPE_8__ {int size; int refptr; int val; void* type; int /*<<< orphan*/  fail; int /*<<< orphan*/  jump; void* cond; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ RAnalOp ;

/* Variables and functions */
 int ARC_REG_LIMM ; 
 int ARC_REG_PCL ; 
 void* R_ANAL_OP_TYPE_ABS ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMOV ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_IO ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOT ; 
 void* R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_ROL ; 
 void* R_ANAL_OP_TYPE_ROR ; 
 void* R_ANAL_OP_TYPE_SAL ; 
 void* R_ANAL_OP_TYPE_SAR ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_XCHG ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 void* SEX_S12 (int) ; 
 int SEX_S13 (int) ; 
 int /*<<< orphan*/  arccompact_dump_fields (int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  arcompact_genops_jmp (TYPE_2__*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* map_cond2radare (int) ; 

__attribute__((used)) static int arcompact_genops(RAnalOp *op, ut64 addr, ut32 words[2]) {
	arc_fields fields = {0};

	fields.format = (words[0] & 0x00c00000) >> 22;
	fields.subopcode = (words[0] & 0x003f0000) >> 16;
	fields.c = (words[0] & 0x00000fc0) >> 6;
	fields.a = (words[0] & 0x0000003f);
	fields.b = (words[0] & 0x07000000) >> 24 | (words[0] & 0x7000) >> 9;
	fields.mode_n = 0;

	/* increase the size to cover any limm reg fields */
	if (fields.b == ARC_REG_LIMM) {
		op->size = 8;
		fields.limm = words[1];
		/* FIXME: MOV<.f> 0,x is encoded as fields.b == ARC_REG_LIMM, but no limm */
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

	if (fields.format == 1) {
		/* REG_U6IMM */
		fields.imm = fields.c;
	} else if (fields.format == 2) {
		/* REG_S12IMM */
		fields.imm = SEX_S12 (fields.c | fields.a << 6);
	}

	switch (fields.subopcode) {
	case 0x00: /* add */
		if ((fields.format == 1 || fields.format == 2) && fields.b == ARC_REG_PCL) {
			/* dst = PCL + src */
			op->ptr = (addr & ~3) + fields.imm;
			op->refptr = 1; /* HACK! we don't actually know what size it is */
		}
	case 0x01: /* add with carry */
	case 0x14: /* add with left shift by 1 */
	case 0x15: /* add with left shift by 2 */
	case 0x16: /* add with left shift by 3 */
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 0x02: /* subtract */
	case 0x03: /* subtract with carry */
	case 0x0e: /* reverse subtract */
	case 0x17: /* subtract with left shift by 1 */
	case 0x18: /* subtract with left shift by 2 */
	case 0x19: /* subtract with left shift by 3 */
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case 0x04: /* logical bitwise AND */
	case 0x06: /* logical bitwise AND with invert */
	case 0x10: /* bit clear */
	case 0x13: /* bit mask */
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case 0x05: /* logical bitwise OR */
	case 0x0f: /* bit set */
		op->type = R_ANAL_OP_TYPE_OR;
		break;
	case 0x07: /* logical bitwise exclusive-OR */
	case 0x12: /* bit xor */
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case 0x08: /* larger of 2 signed integers */
	case 0x09: /* smaller of 2 signed integers */
		op->type = R_ANAL_OP_TYPE_CMOV;
		break;
	case 0x0a: /* move */
		if (fields.format == 2) {
			op->type = R_ANAL_OP_TYPE_MOV;
			op->val = SEX_S12 (fields.a << 6 | fields.c);
		} else if (fields.format == 3) {
			fields.cond = fields.a & 0x1f;
			op->cond = map_cond2radare (fields.cond);
			op->type = R_ANAL_OP_TYPE_CMOV;
			if ((fields.a & 0x20)) {
				/* its a move from imm u6 */
				op->val = fields.c;
			} else if (fields.c == ARC_REG_LIMM) {
				/* its a move from limm */
				op->val = fields.limm;
			}
		}
		break;
	case 0x0b: /* test */
	case 0x0c: /* compare */
	case 0x0d: /* reverse compare */
	case 0x11: /* bit test */
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case 0x1a: /* 32 X 32 signed multiply */
	case 0x1b: /* 32 X 32 signed multiply */
	case 0x1c: /* 32 X 32 unsigned multiply */
	case 0x1d: /* 32 X 32 unsigned multiply */
		op->type = R_ANAL_OP_TYPE_MUL;
		break;
	case 0x21: /* Jump with delay slot */
		fields.mode_n = 1;
	/* fall through */
	case 0x20: /* Jump */
		fields.mode_m = (words[0] & 0x20) >> 5;
		arcompact_genops_jmp (op, addr, &fields, R_ANAL_OP_TYPE_JMP);
		break;
	case 0x23: /* jump and link with delay slot */
		fields.mode_n = 1;
	/* fall through */
	case 0x22: /* jump and link */
		fields.mode_m = (words[0] & 0x20) >> 5;
		arcompact_genops_jmp (op, addr, &fields, R_ANAL_OP_TYPE_CALL);
		break;
	case 0x1e: /* Reserved */
	case 0x1f: /* Reserved */
	case 0x24: /* Reserved */
	case 0x25: /* Reserved */
	case 0x26: /* Reserved */
	case 0x27: /* Reserved */
	case 0x2c: /* Reserved */
	case 0x2d: /* Reserved */
	case 0x2e: /* Reserved */
	case 0x38: /* Reserved */
	case 0x39: /* Reserved */
	case 0x3a: /* Reserved */
	case 0x3b: /* Reserved */
	case 0x3c: /* Reserved */
	case 0x3d: /* Reserved */
	case 0x3e: /* Reserved */
	case 0x3f: /* Reserved */
		op->type = R_ANAL_OP_TYPE_ILL;
		break;
	case 0x28: /* loop (16-bit aligned target address) */
		/* this is essentially a COME FROM instruction!! */
		/* TODO: describe it to radare better? */
		switch (fields.format) {
		case 2: /* Loop Set Up (Unconditional) */
			fields.imm = SEX_S13 ((fields.c | (fields.a << 6)) << 1);
			op->jump = (addr & ~3) + fields.imm;
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			break;
		case 3: /* Loop Set Up (Conditional) */
			fields.imm = fields.c << 1;
			fields.cond = fields.a & 0x1f;
			op->cond = map_cond2radare (fields.a & 0x1f);
			op->jump = (addr & ~3) + fields.imm;
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			break;
		default:
			op->type = R_ANAL_OP_TYPE_ILL;
			break;
		}
		break;
	case 0x29: /* set status flags */
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 0x2a: /* load from auxiliary register. */
	case 0x2b: /* store to auxiliary register. */
		op->type = R_ANAL_OP_TYPE_IO;
		break;
	case 0x2f: /* Single Operand Instructions, 0x04, [0x2F, 0x00 - 0x3F] */
		switch (fields.a) {
		case 0: /* Arithmetic shift left by one */
			op->type = R_ANAL_OP_TYPE_SAL;
			break;
		case 1: /* Arithmetic shift right by one */
			op->type = R_ANAL_OP_TYPE_SAR;
			break;
		case 2: /* Logical shift right by one */
			op->type = R_ANAL_OP_TYPE_SHR;
			break;
		case 3: /* Rotate right */
		case 4: /* Rotate right through carry */
			op->type = R_ANAL_OP_TYPE_ROR;
			break;
		case 5: /* Sign extend byte */
		case 6: /* Sign extend word */
		case 7: /* Zero extend byte */
		case 8: /* Zero extend word */
			// op->type = R_ANAL_OP_TYPE_UNK;
			op->type = R_ANAL_OP_TYPE_MOV;
			/* TODO: a better encoding for SEX and EXT instructions */
			break;
		case 9: /* Absolute */
			op->type = R_ANAL_OP_TYPE_ABS;
			break;
		case 0xa: /* Logical NOT */
			op->type = R_ANAL_OP_TYPE_NOT;
			break;
		case 0xb: /* Rotate left through carry */
			op->type = R_ANAL_OP_TYPE_ROL;
			break;
		case 0xc: /* Atomic Exchange */
			op->type = R_ANAL_OP_TYPE_XCHG;
			break;
		case 0x3f: /* See Zero operand (ZOP) table */
			switch (fields.b) {
			case 1: /* Sleep */
				/* TODO: a better encoding for this */
				op->type = R_ANAL_OP_TYPE_NULL;
				break;
			case 2: /* Software interrupt */
				op->type = R_ANAL_OP_TYPE_SWI;
				break;
			case 3: /* Wait for all data-based memory transactions to complete */
				/* TODO: a better encoding for this */
				op->type = R_ANAL_OP_TYPE_NULL;
				break;
			case 4: /* Return from interrupt/exception */
				op->type = R_ANAL_OP_TYPE_RET;
				break;
			case 5: /* Breakpoint instruction */
				op->type = R_ANAL_OP_TYPE_TRAP;
				break;
			default:
				op->type = R_ANAL_OP_TYPE_ILL;
				break;
			}
			break;
		default:
			op->type = R_ANAL_OP_TYPE_ILL;
			break;
		}
		break;
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37: /* Load Register-Register, 0x04, [0x30 - 0x37] */
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	}

	arccompact_dump_fields (addr, words, &fields);
	return op->size;
}