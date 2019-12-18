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
struct TYPE_3__ {int size; int /*<<< orphan*/  esil; int /*<<< orphan*/  dst; int /*<<< orphan*/ * src; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SOURCE_REG (int) ; 
 int /*<<< orphan*/  GET_TARGET_REG (int) ; 
 int /*<<< orphan*/  LONG_SIZE ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_STORE ; 
 int /*<<< orphan*/  anal_fill_ai_rg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anal_fill_reg_disp_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int movl_reg_rdisp(RAnal* anal, RAnalOp* op, ut16 code) {
	op->type = R_ANAL_OP_TYPE_STORE;
	op->src[0] = anal_fill_ai_rg (anal, GET_SOURCE_REG (code));
	op->dst = anal_fill_reg_disp_mem (anal, GET_TARGET_REG (code), code & 0x0F, LONG_SIZE);
	r_strbuf_setf (&op->esil, "r%d,r%d,0x%x,+,=[4]", GET_SOURCE_REG (code), GET_TARGET_REG (code), (code & 0xF) << 2);
	return op->size;
}