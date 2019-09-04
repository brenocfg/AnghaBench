#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_6__ {int /*<<< orphan*/  esil; TYPE_1__** src; TYPE_1__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_1__ RAnalValue ;
typedef  TYPE_2__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 TYPE_1__* r_anal_value_new () ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regs_16_alt ; 

__attribute__((used)) static inline void gb_anal_pp (RReg *reg, RAnalOp *op, const ut8 data)		//push , pop
{
	RAnalValue *val = r_anal_value_new ();
	val->reg = r_reg_get (reg, regs_16_alt[(data>>4) - 12], R_REG_TYPE_GPR);
	if ((data & 0xf) == 1) {
		op->dst = val;
		r_strbuf_setf (&op->esil, "sp,[2],%s,=,2,sp,+=", regs_16_alt[(data>>4) - 12]);		//pop
	} else {
		op->src[0] = val;
		r_strbuf_setf (&op->esil, "2,sp,-=,%s,sp,=[2]", regs_16_alt[(data>>4) - 12]);		//push
	}
}