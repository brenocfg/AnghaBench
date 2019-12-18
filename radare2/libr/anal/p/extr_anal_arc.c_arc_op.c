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
typedef  int ut8 ;
typedef  void* ut64 ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int size; void* type; void* jump; void* fail; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_ROR ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int arcompact_op (TYPE_2__*,TYPE_1__*,void*,int const*,int) ; 
 int r_read_le32 (int const*) ; 

__attribute__((used)) static int arc_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len, RAnalOpMask mask) {
	const ut8 *b = (ut8 *)data;

	if (anal->bits == 16) {
		return arcompact_op (anal, op, addr, data, len);
	}

	/* ARCtangent A4 */
	op->size = 4;
	op->fail = addr + 4;
	ut8 basecode = (len > 3)? ((b[3] & 0xf8) >> 3): 0;
	switch (basecode) {
	case 0x04: /* Branch */
	case 0x05: /* Branch with Link */
	case 0x06: /* Loop */
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = addr + 4 + ((r_read_le32 (&data[0]) & 0x07ffff80) >> (7 - 2));
		break;
	case 0x07: /* Conditional Jump and Jump with Link */
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = 0;
		break;
	case 0x08:
	case 0x09:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 0x0a:
	case 0x0b:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case 0x0c:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case 0x0d:
		op->type = R_ANAL_OP_TYPE_OR;
		break;
	case 0x0f:
		if ((b[0] == 0xff) && (b[1] == 0xff)) {
			op->type = R_ANAL_OP_TYPE_NOP;
			break;
		}
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case 0x13:
		op->type = R_ANAL_OP_TYPE_ROR;
		break;
	default:
		break;
	}
	return op->size;
}