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
struct TYPE_7__ {int type; int /*<<< orphan*/  esil; TYPE_2__** src; TYPE_1__* dst; } ;
struct TYPE_6__ {int memref; void* reg; } ;
struct TYPE_5__ {void* reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
#define  R_ANAL_OP_TYPE_ADD 133 
#define  R_ANAL_OP_TYPE_AND 132 
#define  R_ANAL_OP_TYPE_CMP 131 
#define  R_ANAL_OP_TYPE_OR 130 
#define  R_ANAL_OP_TYPE_SUB 129 
#define  R_ANAL_OP_TYPE_XOR 128 
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 void* r_reg_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char*) ; 
 char** regs_x ; 

__attribute__((used)) static void gb_anal_xoaasc (RReg *reg, RAnalOp *op, const ut8 *data) {
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->dst->reg = r_reg_get (reg, "a", R_REG_TYPE_GPR);
	op->src[0]->reg = r_reg_get (reg, regs_x[data[0] & 7], R_REG_TYPE_GPR);
	op->src[0]->memref = ((data[0] & 7) == 6);
	switch (op->type) {
	case R_ANAL_OP_TYPE_XOR:
		if (op->src[0]->memref) {
			r_strbuf_setf (&op->esil, "%s,[1],a,^=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", regs_x[data[0] & 7]);
		} else {
			r_strbuf_setf (&op->esil, "%s,a,^=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", regs_x[data[0] & 7]);
		}
		break;
	case R_ANAL_OP_TYPE_OR:
		if (op->src[0]->memref) {
			r_strbuf_setf (&op->esil, "%s,[1],a,|=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", regs_x[data[0] &7]);
		} else {
			r_strbuf_setf (&op->esil, "%s,a,|=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", regs_x[data[0] & 7]);
		}
		break;
	case R_ANAL_OP_TYPE_AND:
		if (op->src[0]->memref) {
			r_strbuf_setf (&op->esil, "%s,[1],a,&=,$z,Z,:=,0,N,:=,1,H,:=,0,C,:=", regs_x[data[0] & 7]);
		} else {
			r_strbuf_setf (&op->esil, "%s,a,&=,$z,Z,:=,0,N,:=,1,H,:=,0,C,:=", regs_x[data[0] & 7]);
		}
		break;
	case R_ANAL_OP_TYPE_ADD:
		if (op->src[0]->memref) {
			if (data[0] > 0x87) {
				op->src[1] = r_anal_value_new ();
				op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
				r_strbuf_setf ( &op->esil, "C,%s,[1],+,a,+=,$z,Z,:=,3,$c,H,:=,7,$c,C,:=,0,N,:=", regs_x[data[0] & 7]);
			} else {
				r_strbuf_setf (&op->esil, "%s,[1],a,+=,$z,Z,:=,3,$c,H,:=,7,$c,C,:=,0,N,:=", regs_x[data[0] & 7]);
			}
		} else {
			if (data[0] > 0x87) {
				op->src[1] = r_anal_value_new ();
				op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
				r_strbuf_setf (&op->esil, "C,%s,+,a,+=,$z,Z,:=,3,$c,H,:=,7,$c,C,:=,0,N,:=", regs_x[data[0] & 7]);
			} else {
				r_strbuf_setf (&op->esil, "%s,a,+=,$z,Z,:=,3,$c,H,:=,7,$c,C,:=,0,N,:=", regs_x[data[0] & 7]);
			}
		}
		break;
	case R_ANAL_OP_TYPE_SUB:
		if (op->src[0]->memref) {
			if (data[0] > 0x97) {
				op->src[1] = r_anal_value_new ();
				op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
				r_strbuf_setf (&op->esil, "C,%s,[1],+,a,-=,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
			} else {
				r_strbuf_setf (&op->esil, "%s,[1],a,-=,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
			}
		} else {
			if (data[0] > 0x97) {
				op->src[1] = r_anal_value_new ();
				op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
				r_strbuf_setf (&op->esil, "C,%s,+,a,-=,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
			} else {
				r_strbuf_setf (&op->esil, "%s,a,-=,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
			}
		}
		break;
	case R_ANAL_OP_TYPE_CMP:
		if (op->src[0]->memref) {
			r_strbuf_setf (&op->esil, "%s,[1],a,==,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
		} else {
			r_strbuf_setf (&op->esil, "%s,a,==,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", regs_x[data[0] & 7]);
		}
		break;
	default:
		// not handled yet
		break;
	}
}