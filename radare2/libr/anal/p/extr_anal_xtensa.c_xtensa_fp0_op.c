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
struct TYPE_4__ {void* type; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_FPU ; 
 void* R_ANAL_OP_TYPE_ABS ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOT ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 int /*<<< orphan*/  xtensa_unk_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void xtensa_fp0_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	op->family = R_ANAL_OP_FAMILY_FPU;
	switch ((buf[2] >> 4) & 0xf) {
	case 0x0: case 0x4:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 0x1: case 0x5:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case 0x2:
		op->type = R_ANAL_OP_TYPE_MUL;
		break;
	case 0x8: case 0x9: case 0xa: case 0xb:
	case 0xc: case 0xd: case 0xe:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 0xf:
		switch ((buf[0] >> 4) & 0xf) {
		case 0x0: case 0x4: case 0x5:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case 0x1:
			op->type = R_ANAL_OP_TYPE_ABS;
			break;
		case 0x6:
			op->type = R_ANAL_OP_TYPE_NOT;
			break;
		default:
			xtensa_unk_op (anal, op, addr, buf);
			break;
		}
		break;
	default:
		xtensa_unk_op (anal, op, addr, buf);
		break;
	}
}