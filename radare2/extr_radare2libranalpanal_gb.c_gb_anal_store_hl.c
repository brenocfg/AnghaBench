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
struct TYPE_7__ {int /*<<< orphan*/  esil; TYPE_2__** src; TYPE_1__* dst; } ;
struct TYPE_6__ {int absolute; int imm; void* reg; } ;
struct TYPE_5__ {int memref; void* reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 void* r_reg_get (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int const) ; 
 int const* regs_8 ; 

__attribute__((used)) static inline void gb_anal_store_hl (RReg *reg, RAnalOp *op, const ut8 *data) {
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->dst->reg = r_reg_get (reg, "hl", R_REG_TYPE_GPR);
	op->dst->memref = 1;
	op->src[0]->absolute = true;
	if (data[0] == 0x36) {
		op->src[0]->imm = data[1];
		r_strbuf_setf (&op->esil, "0x%02x,hl,=[1]", data[1]);
	} else {
		op->src[0]->reg = r_reg_get (reg, regs_8[data[0] & 0x07], R_REG_TYPE_GPR);
		r_strbuf_setf (&op->esil, "%s,hl,=[1]", regs_8[data[0] & 0x07]);
	}
	if (data[0] == 0x32) {
		r_strbuf_set (&op->esil, "a,hl,=[1],1,hl,-=");
	}
	if (data[0] == 0x22) {
		r_strbuf_set (&op->esil, "a,hl,=[1],1,hl,+=");
	}
}