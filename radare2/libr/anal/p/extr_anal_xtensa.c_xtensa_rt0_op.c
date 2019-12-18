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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_MOV ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NOT ; 
 int /*<<< orphan*/  xtensa_unk_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void xtensa_rt0_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	switch (buf[1] & 0xf) {
	case 0:
		op->type = R_ANAL_OP_TYPE_NOT;
		break;
	case 1:
		/*op->type = R_ANAL_OP_TYPE_ABS;*/
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	default:
		xtensa_unk_op (anal, op, addr, buf);
		break;
	}
}