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
struct TYPE_6__ {int imm; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int const) ; 

__attribute__((used)) static inline void gb_anal_add_sp (RReg *reg, RAnalOp *op, const ut8 data) {
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->dst->reg = r_reg_get (reg, "sp", R_REG_TYPE_GPR);
	op->src[0]->imm = (st8)data;
	if (data < 128) {
		r_strbuf_setf (&op->esil, "0x%02x,sp,+=", data);
	} else {
		r_strbuf_setf (&op->esil, "0x%02x,sp,-=", 0 - (st8)data);
	}
	r_strbuf_append (&op->esil, ",0,Z,=,0,N,:=");
}