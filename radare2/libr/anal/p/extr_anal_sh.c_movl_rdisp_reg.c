#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut16 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  esil; int /*<<< orphan*/ * src; int /*<<< orphan*/  dst; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SOURCE_REG (int) ; 
 int /*<<< orphan*/  GET_TARGET_REG (int) ; 
 int /*<<< orphan*/  LONG_SIZE ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_LOAD ; 
 int /*<<< orphan*/  anal_fill_ai_rg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anal_fill_reg_disp_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int movl_rdisp_reg(RAnal* anal, RAnalOp* op, ut16 code) {
	op->type = R_ANAL_OP_TYPE_LOAD;
	op->dst = anal_fill_ai_rg (anal, GET_TARGET_REG (code));
	op->src[0] = anal_fill_reg_disp_mem (anal, GET_SOURCE_REG (code), code & 0x0F, LONG_SIZE);
	r_strbuf_setf (&op->esil, "r%d,0x%x,+,[4],r%d,=", GET_SOURCE_REG (code), (code&0xF) * 4, GET_TARGET_REG (code));
	return op->size;
}