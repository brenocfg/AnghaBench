#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_9__ {int /*<<< orphan*/  disp; } ;
struct TYPE_11__ {TYPE_3__ mem; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int type; TYPE_2__* dst; TYPE_1__** src; } ;
struct TYPE_8__ {int /*<<< orphan*/  delta; int /*<<< orphan*/ * reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  delta; int /*<<< orphan*/ * reg; } ;
typedef  int /*<<< orphan*/  RRegItem ;
typedef  TYPE_4__ RAnalOp ;

/* Variables and functions */
 TYPE_6__ INSOP (int) ; 
#define  R_ANAL_OP_TYPE_LOAD 129 
 int R_ANAL_OP_TYPE_MASK ; 
#define  R_ANAL_OP_TYPE_STORE 128 
 int /*<<< orphan*/  SPARC_OP_MEM ; 
 int /*<<< orphan*/  ZERO_FILL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_reg_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* r_anal_value_new () ; 

__attribute__((used)) static void op_fillval(RAnalOp *op, csh handle, cs_insn *insn) {
	static RRegItem reg;
	switch (op->type & R_ANAL_OP_TYPE_MASK) {
	case R_ANAL_OP_TYPE_LOAD:
		if (INSOP(0).type == SPARC_OP_MEM) {
			ZERO_FILL (reg);
			op->src[0] = r_anal_value_new ();
			op->src[0]->reg = &reg;
			parse_reg_name (op->src[0]->reg, handle, insn, 0);
			op->src[0]->delta = INSOP(0).mem.disp;
		}
		break;
	case R_ANAL_OP_TYPE_STORE:
		if (INSOP(1).type == SPARC_OP_MEM) {
			ZERO_FILL (reg);
			op->dst = r_anal_value_new ();
			op->dst->reg = &reg;
			parse_reg_name (op->dst->reg, handle, insn, 1);
			op->dst->delta = INSOP(1).mem.disp;
		}
		break;
	}
}