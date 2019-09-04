#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int size; int /*<<< orphan*/  fail; void* jump; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CALL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_JMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_LOAD ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NULL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_RET ; 
 void* getaddr (int /*<<< orphan*/ ,int const*) ; 
 int hackyArmAnal (int /*<<< orphan*/ *,TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arm_op64(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *d, int len) {
	memset (op, 0, sizeof (RAnalOp));
	if (d[3] == 0) {
		return -1;      // invalid
	}
	int haa = hackyArmAnal (anal, op, d, len);
	if (haa > 0) {
		return haa;
	}
	op->size = 4;
	op->type = R_ANAL_OP_TYPE_NULL;
	if (d[0] == 0xc0 && d[3] == 0xd6) {
		// defaults to x30 reg. but can be different
		op->type = R_ANAL_OP_TYPE_RET;
	}
	switch (d[3]) {
	case 0x71:
	case 0xeb:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case 0xb8:
	case 0xb9:
	case 0xf8:
	case 0xa9: // ldp/stp
	case 0xf9: // ldr/str
		op->type = R_ANAL_OP_TYPE_LOAD;
		break;
	case 0x91: // mov
	case 0x52: // mov
	case 0x94: // bl A
	case 0x97: // bl A
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = getaddr (addr, d);
		op->fail = addr + 4;
		break;
	case 0x54: // beq A
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = addr + (4 * ((d[0] >> 4) | (d[1] << 8) | (d[2] << 16)));
		op->fail = addr + 4;
		break;
	case 0x17: // b A
	case 0x14: // b A
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = getaddr (addr, d);
		op->fail = addr + 4;
		break;
	}
	return op->size;
}