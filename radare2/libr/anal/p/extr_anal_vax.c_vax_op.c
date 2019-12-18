#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int size; void* type; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 

__attribute__((used)) static int vax_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	op->size = 1;
	if (len < 1) {
		return -1;
	}
	op->type = R_ANAL_OP_TYPE_UNK;
	switch (buf[0]) {
	case 0xd0:
	case 0x2e:
		op->type = R_ANAL_OP_TYPE_MOV;
		op->size = 8;
		break;
	case 0x78:
		op->type = R_ANAL_OP_TYPE_SHL;
		op->size = 8;
		break;
	case 0xc0:
	case 0xd8:
		op->type = R_ANAL_OP_TYPE_ADD;
		op->size = 8;
		break;
	case 0x00:
		op->type = R_ANAL_OP_TYPE_TRAP; // HALT
		break;
	case 0x01:
		op->type = R_ANAL_OP_TYPE_NOP;
		break;
	case 0x51:
	case 0x73:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case 0xac:
		op->type = R_ANAL_OP_TYPE_XOR;
		op->size = 4;
		break;
	case 0x5a:
		op->size = 2;
		break;
	case 0x11:
	case 0x18:
		op->size = 2;
		op->type = R_ANAL_OP_TYPE_CJMP;
		break;
	case 0x31:
	case 0xe9:
		op->size = 3;
		op->type = R_ANAL_OP_TYPE_CJMP;
		break;
	case 0xc6:
	case 0xc7:
		op->size = 8;
		op->type = R_ANAL_OP_TYPE_DIV;
		break;
	case 0xd6:
	case 0x61:
		op->size = 2;
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 0x62:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case 0xff:
		op->size = 2;
		break;
	}
	return op->size;
}