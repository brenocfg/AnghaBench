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
struct TYPE_4__ {void* type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_IO ; 
 void* R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 int /*<<< orphan*/  xtensa_unk_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void xtensa_st1_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	switch ((buf[1] >> 4) & 0xf) {
	case 0x0: case 0x1: case 0x2: case 0x3:
	case 0x4:
		/* Set shift-amount-register */
		op->type = R_ANAL_OP_TYPE_NULL;
		/*op->type = R_ANAL_OP_TYPE_MOV;*/
		break;
	case 0x6: case 0x7:
		op->type = R_ANAL_OP_TYPE_IO;
		/*op->type = R_ANAL_OP_TYPE_MOV;*/
		break;
	case 0x8:
		op->type = R_ANAL_OP_TYPE_SWI;
		break;
	case 0xe: case 0xf:
		op->type = R_ANAL_OP_TYPE_NULL;
		break;
	default:
		xtensa_unk_op (anal, op, addr, buf);
		break;
	}
}