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
struct TYPE_7__ {int /*<<< orphan*/  esil; TYPE_2__* dst; TYPE_1__** src; } ;
struct TYPE_6__ {void* reg; } ;
struct TYPE_5__ {int memref; int absolute; void* reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 void* r_reg_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char*) ; 
 char** regs_8 ; 

__attribute__((used)) static inline void gb_anal_load_hl (RReg *reg, RAnalOp *op, const ut8 data)	//load with [hl] as memref
{
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->src[0]->reg = r_reg_get (reg, "hl", R_REG_TYPE_GPR);
	op->src[0]->memref = 1;
	op->src[0]->absolute = true;
	op->dst->reg = r_reg_get (reg, regs_8[((data & 0x38)>>3)], R_REG_TYPE_GPR);
	r_strbuf_setf (&op->esil, "hl,[1],%s,=", regs_8[((data & 0x38)>>3)]);
	if (data == 0x3a) {
		r_strbuf_append (&op->esil, ",1,hl,-=");
	}
	if (data == 0x2a) {
		r_strbuf_set (&op->esil, "hl,[1],a,=,1,hl,+=");			//hack in concept
	}
}