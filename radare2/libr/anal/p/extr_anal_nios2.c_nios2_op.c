#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int size; void* type; int /*<<< orphan*/  esil; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nios2_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *b, int len, RAnalOpMask mask) {
	if (!op) {
		return 1;
	}
	/* Ayeeee! What's inside op? Do we have an initialized RAnalOp? Are we going to have a leak here? :-( */
	memset (op, 0, sizeof (RAnalOp)); /* We need to refactorize this. Something like r_anal_op_init would be more appropriate */
	r_strbuf_init (&op->esil);
	op->size = 4;

	if ((b[0]&0xff) == 0x3a) {
		// XXX
		op->type = R_ANAL_OP_TYPE_RET;
	} else
	if ((b[0]&0xf) == 0xa) {
		op->type = R_ANAL_OP_TYPE_JMP;
	} else
	if ((b[0]&0xf) == 4) {
		op->type = R_ANAL_OP_TYPE_ADD;
	} else
	if ((b[0]&0xf) == 5) {
		op->type = R_ANAL_OP_TYPE_STORE;
	} else
	if ((b[0]&0xf) == 6) {
		// blt, r19, r5, 0x8023480
		op->type = R_ANAL_OP_TYPE_CJMP;
		// TODO: address
	} else
	if ((b[0]&0xf) == 7) {
		// blt, r19, r5, 0x8023480
		op->type = R_ANAL_OP_TYPE_LOAD;
		// TODO: address
	} else {
		switch (b[0]) {
		case 0x3a:
			if (b[1] >= 0xa0 && b[1] <= 0xaf && b[3] == 0x3d) {
				op->type = R_ANAL_OP_TYPE_TRAP;
			} else if ((b[1] >= 0xe0 && b[1] <= 0xe7) && b[2] == 0x3e && !b[3]) {
				// nextpc ra
				op->type = R_ANAL_OP_TYPE_RET;
			}
			break;
		case 0x01:
			// jmpi
			op->type = R_ANAL_OP_TYPE_JMP;
			break;
		case 0x00:
		case 0x20:
		case 0x40:
		case 0x80:
		case 0xc0:
			//
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		case 0x26:
			// beq
			break;
		case 0x07:
		case 0x47:
		case 0x87:
		case 0xc7:
			// ldb
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x0d:
		case 0x2d:
		case 0x4d:
		case 0x8d:
		case 0xcd:
			// sth && sthio
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case 0x06:
		case 0x46:
		case 0x86:
		case 0xc6:
			// br
			op->type = R_ANAL_OP_TYPE_CALL;
			break;
		}
	}
	return op->size;
}