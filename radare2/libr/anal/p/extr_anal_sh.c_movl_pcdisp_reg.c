#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut16 ;
struct TYPE_4__ {int addr; int size; int /*<<< orphan*/  esil; int /*<<< orphan*/  dst; int /*<<< orphan*/ * src; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  GET_TARGET_REG (int) ; 
 int /*<<< orphan*/  LONG_SIZE ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_LOAD ; 
 int /*<<< orphan*/  anal_fill_ai_rg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anal_pcrel_disp_mov (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int movl_pcdisp_reg(RAnal* anal, RAnalOp* op, ut16 code) {
	op->type = R_ANAL_OP_TYPE_LOAD;
	op->src[0] = anal_pcrel_disp_mov (anal, op, code & 0xFF, LONG_SIZE);
	//TODO: check it
	op->dst = anal_fill_ai_rg (anal, GET_TARGET_REG (code));
	//r_strbuf_setf (&op->esil, "0x%x,[4],r%d,=", (code & 0xFF) * 4 + (op->addr & 0xfffffff3) + 4, GET_TARGET_REG (code));
	r_strbuf_setf (&op->esil, "0x%x,[4],r%d,=", (code & 0xFF) * 4 + ((op->addr >> 2)<<2) + 4, GET_TARGET_REG (code));
	return op->size;
}