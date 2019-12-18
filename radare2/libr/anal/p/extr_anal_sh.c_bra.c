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
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_4__ {int delay; int eob; int size; int /*<<< orphan*/  jump; int /*<<< orphan*/  esil; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BRA_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_JMP ; 
 int /*<<< orphan*/  disarm_12bit_offset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bra(RAnal* anal, RAnalOp* op, ut16 code) {
	/* Unconditional branch, relative to PC */
	op->type = R_ANAL_OP_TYPE_JMP;
	op->delay = 1;
	op->jump = disarm_12bit_offset (op, GET_BRA_OFFSET (code));
	op->eob = true;
	r_strbuf_setf (&op->esil, "1,SETD,0x%x,pc,=", op->jump);
	return op->size;
}