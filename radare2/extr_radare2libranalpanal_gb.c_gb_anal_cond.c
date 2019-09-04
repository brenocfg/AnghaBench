#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_7__ {TYPE_1__* dst; int /*<<< orphan*/  cond; TYPE_2__** src; } ;
struct TYPE_6__ {int imm; } ;
struct TYPE_5__ {void* reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_COND_EQ ; 
 int /*<<< orphan*/  R_ANAL_COND_NE ; 
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 void* r_reg_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regs_1 ; 

__attribute__((used)) static inline void gb_anal_cond (RReg *reg, RAnalOp *op, const ut8 data) {
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->src[0]->imm = 1;
	if (data & 0x8) {
		op->cond = R_ANAL_COND_EQ;
	} else {
		op->cond = R_ANAL_COND_NE;
	}
	switch (data) {
	case 0x20:
	case 0x28:
	case 0xc0:
	case 0xc2:
	case 0xc4:
	case 0xc8:
	case 0xca:
	case 0xcc:
		op->dst->reg = r_reg_get (reg, regs_1[0], R_REG_TYPE_GPR);
		break;
	default:
		op->dst->reg = r_reg_get (reg, regs_1[3], R_REG_TYPE_GPR);
	}
}