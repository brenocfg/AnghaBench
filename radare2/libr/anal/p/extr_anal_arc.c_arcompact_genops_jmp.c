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
struct TYPE_7__ {int cond; int a; int format; int c; int limm; int imm; int /*<<< orphan*/  mode_n; int /*<<< orphan*/  mode_m; } ;
typedef  TYPE_1__ arc_fields ;
struct TYPE_8__ {int type; int size; void* cond; int /*<<< orphan*/  delay; } ;
typedef  TYPE_2__ RAnalOp ;

/* Variables and functions */
 int ARC_REG_BLINK ; 
 int ARC_REG_ILINK1 ; 
 int ARC_REG_ILINK2 ; 
 int ARC_REG_LIMM ; 
#define  R_ANAL_OP_TYPE_CALL 129 
 int R_ANAL_OP_TYPE_CCALL ; 
 int R_ANAL_OP_TYPE_CJMP ; 
 int R_ANAL_OP_TYPE_CRET ; 
#define  R_ANAL_OP_TYPE_JMP 128 
 int R_ANAL_OP_TYPE_RET ; 
 int R_ANAL_OP_TYPE_UCALL ; 
 int R_ANAL_OP_TYPE_UCCALL ; 
 int R_ANAL_OP_TYPE_UCJMP ; 
 int R_ANAL_OP_TYPE_UJMP ; 
 int SEX_S12 (int) ; 
 int /*<<< orphan*/  arcompact_jump (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcompact_jump_cond (TYPE_2__*,int,int,int /*<<< orphan*/ ,int) ; 
 void* map_cond2radare (int) ; 

__attribute__((used)) static int arcompact_genops_jmp(RAnalOp *op, ut64 addr, arc_fields *f, ut64 basic_type) {
	ut64 type_ujmp;
	ut64 type_cjmp;
	ut64 type_ucjmp;

	switch (basic_type) {
	case R_ANAL_OP_TYPE_JMP:
		type_ujmp = R_ANAL_OP_TYPE_UJMP;
		type_cjmp = R_ANAL_OP_TYPE_CJMP;
		type_ucjmp = R_ANAL_OP_TYPE_UCJMP;
		break;
	case R_ANAL_OP_TYPE_CALL:
		type_ujmp = R_ANAL_OP_TYPE_UCALL;
		type_cjmp = R_ANAL_OP_TYPE_CCALL;
		type_ucjmp = R_ANAL_OP_TYPE_UCCALL;
		break;
	default:
		return -1; /* Should not happen */
	}

	f->cond = f->a & 0x1f;

	switch (f->format) {
	case 0: /* unconditional jumps via reg or long imm */
		if (f->c == ARC_REG_LIMM) {
			/* limm */
			op->type = basic_type;
			arcompact_jump (op, addr, f->limm, f->mode_n);
			return op->size;
		}
		if (f->c == ARC_REG_ILINK1 || f->c == ARC_REG_ILINK2 || f->c == ARC_REG_BLINK) {
			/* ilink1, ilink2, blink */
			/* Note: not valid for basic_type == CALL */
			op->type = R_ANAL_OP_TYPE_RET;
			op->delay = f->mode_n;
			return op->size;
		}
		op->type = type_ujmp;
		return op->size;
	case 1: /* unconditional jumps via u6 imm */
		op->type = basic_type;
		arcompact_jump (op, addr, f->c, f->mode_n);
		return op->size;
	case 2: /* unconditional jumps via s12 imm */
		op->type = basic_type;
		f->imm = (f->a << 6 | f->c);
		f->imm = SEX_S12 (f->imm);
		arcompact_jump (op, addr, f->imm, f->mode_n);
		return op->size;
	case 3: /* conditional jumps */
		if (f->mode_m == 0) {
			if (f->c == ARC_REG_LIMM) {
				op->type = type_cjmp;
				arcompact_jump_cond (op, addr, f->limm, f->mode_n, f->cond);
				return op->size;
			}
			if (f->c == ARC_REG_ILINK1 || f->c == ARC_REG_ILINK2 || f->c == ARC_REG_BLINK) {
				/* ilink1, ilink2, blink */
				/* Note: not valid for basic_type == CALL */
				op->type = R_ANAL_OP_TYPE_CRET;
				op->cond = map_cond2radare (f->cond);
				op->delay = f->mode_n;
				return op->size;
			}

			op->cond = map_cond2radare (f->cond);
			op->type = type_ucjmp;
			return op->size;
		}

		op->type = type_cjmp;
		arcompact_jump_cond (op, addr, f->c, f->mode_n, f->cond);
		return op->size;
	}

	/* should not be reached */
	return 0;
}