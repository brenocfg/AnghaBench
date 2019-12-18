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
struct TYPE_6__ {int absolute; int imm; void* reg; } ;
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
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int const) ; 

__attribute__((used)) static void gb_anal_xoaasc_imm (RReg *reg, RAnalOp *op, const ut8 *data)	//xor , or, and, add, adc, sub, sbc, cp
{
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->dst->reg = r_reg_get (reg, "a", R_REG_TYPE_GPR);
	op->src[0]->absolute = true;
	op->src[0]->imm = data[1];
	switch (op->type) {
	case R_ANAL_OP_TYPE_XOR:
		r_strbuf_setf (&op->esil, "0x%02x,a,^=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", data[1]);
		break;
	case R_ANAL_OP_TYPE_OR:
		r_strbuf_setf (&op->esil, "0x%02x,a,|=,$z,Z,:=,0,N,:=,0,H,:=,0,C,:=", data[1]);
		break;
	case R_ANAL_OP_TYPE_AND:
		r_strbuf_setf (&op->esil, "0x%02x,a,&=,$z,Z,:=,0,N,:=,1,H,:=,0,C,:=", data[1]);
		break;
	case R_ANAL_OP_TYPE_ADD:
		r_strbuf_setf (&op->esil, "0x%02x,", data[1]);
		if (data[0] == 0xce) {					//adc
			op->src[1] = r_anal_value_new ();
			op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
			r_strbuf_append (&op->esil, "a,+=,C,NUM,7,$c,C,:=,3,$c,H,:=,a,+=,7,$c,C,|,C,:=,3,$c,H,|=,a,a,=,$z,Z,:=,0,N,:=");
		} else {
			r_strbuf_append (&op->esil, "a,+=,3,$c,H,:=,7,$c,C,:=,0,N,:=,a,a,=,$z,Z,:=");
		}
		break;
	case R_ANAL_OP_TYPE_SUB:
		r_strbuf_setf (&op->esil, "0x%02x,", data[1]);
		if (data[0] == 0xde) {					//sbc
			op->src[1] = r_anal_value_new ();
			op->src[1]->reg = r_reg_get (reg, "C", R_REG_TYPE_GPR);
			r_strbuf_append (&op->esil, "a,-=,C,NUM,8,$b,C,:=,4,$b,H,:=,a,-=,8,$b,C,|,C,=,4,$b,H,|,H,=,a,a,=,$z,Z,:=,1,N,:=");
		} else {
			r_strbuf_append (&op->esil, "a,-=,4,$b,H,:=,8,$b,C,:=,1,N,:=,a,a,=,$z,Z,:=");
		}
		break;
	case R_ANAL_OP_TYPE_CMP:
		r_strbuf_setf (&op->esil, "%d,a,==,$z,Z,:=,4,$b,H,:=,8,$b,C,:=,1,N,:=", data[1]);
		break;
	}
}