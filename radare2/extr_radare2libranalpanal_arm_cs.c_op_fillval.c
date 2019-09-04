#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_12__ {int /*<<< orphan*/  scale; int /*<<< orphan*/  index; } ;
struct TYPE_15__ {TYPE_4__ mem; } ;
struct TYPE_11__ {int /*<<< orphan*/  index; } ;
struct TYPE_14__ {TYPE_3__ mem; } ;
struct TYPE_13__ {int type; int /*<<< orphan*/  scale; void* ireg; TYPE_2__* dst; TYPE_1__** src; } ;
struct TYPE_10__ {void* delta; int /*<<< orphan*/ * reg; } ;
struct TYPE_9__ {void* delta; int /*<<< orphan*/ * reg; } ;
typedef  int /*<<< orphan*/  RRegItem ;
typedef  TYPE_5__ RAnalOp ;

/* Variables and functions */
 scalar_t__ HASMEMINDEX (int) ; 
 scalar_t__ HASMEMINDEX64 (int) ; 
 TYPE_8__ INSOP (int) ; 
 TYPE_7__ INSOP64 (int) ; 
 void* MEMDISP (int) ; 
 void* MEMDISP64 (int) ; 
#define  R_ANAL_OP_TYPE_LOAD 129 
 int R_ANAL_OP_TYPE_MASK ; 
#define  R_ANAL_OP_TYPE_STORE 128 
 int /*<<< orphan*/  ZERO_FILL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_reg64_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_reg_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* r_anal_value_new () ; 
 void* r_str_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void op_fillval(RAnalOp *op , csh handle, cs_insn *insn, int bits) {
	static RRegItem reg;
	switch (op->type & R_ANAL_OP_TYPE_MASK) {
	case R_ANAL_OP_TYPE_LOAD:
		op->src[0] = r_anal_value_new ();
		ZERO_FILL (reg);
		op->src[0]->reg = &reg;
		if (bits == 64) {
			parse_reg64_name (op->src[0]->reg, handle, insn, 1);
			op->src[0]->delta = MEMDISP64(1);
		} else {
			parse_reg_name (op->src[0]->reg, handle, insn, 1);
			op->src[0]->delta = MEMDISP(1);
		}
		break;
	case R_ANAL_OP_TYPE_STORE:
		op->dst = r_anal_value_new ();
		ZERO_FILL (reg);
		op->dst->reg = &reg;
		if (bits == 64) {
			parse_reg64_name (op->dst->reg, handle, insn, 1);
			op->dst->delta = MEMDISP64(1);
		} else {
			parse_reg_name (op->dst->reg, handle, insn, 1);
			op->dst->delta = MEMDISP(1);
		}
		break;
	default:
		break;
	}
	if ((bits == 64) && HASMEMINDEX64 (1)) {
		op->ireg = r_str_get (cs_reg_name (handle, INSOP64 (1).mem.index));
	} else if (HASMEMINDEX (1)) {
		op->ireg = r_str_get (cs_reg_name (handle, INSOP (1).mem.index));
		op->scale = INSOP (1).mem.scale;
	}
}