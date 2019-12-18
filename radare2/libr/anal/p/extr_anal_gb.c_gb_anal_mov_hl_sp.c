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
typedef  int const st8 ;
struct TYPE_7__ {int /*<<< orphan*/  esil; TYPE_2__** src; TYPE_1__* dst; } ;
struct TYPE_6__ {int imm; void* reg; } ;
struct TYPE_5__ {void* reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 void* r_reg_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/ * regs_16 ; 

__attribute__((used)) static inline void gb_anal_mov_hl_sp (RReg *reg, RAnalOp *op, const ut8 data) {
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->src[1] = r_anal_value_new ();
	op->dst->reg = r_reg_get (reg, regs_16[2], R_REG_TYPE_GPR);
	op->src[0]->reg = r_reg_get (reg, regs_16[3], R_REG_TYPE_GPR);
	op->src[1]->imm = (st8)data;
	if (data < 128) {
		r_strbuf_setf (&op->esil, "0x%02x,sp,+,hl,=", data);
	} else {
		r_strbuf_setf (&op->esil, "0x%02x,sp,-,hl,=", 0 - (st8)data);
	}
	r_strbuf_append (&op->esil, ",0,Z,=,0,N,:=");
}