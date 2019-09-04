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
struct TYPE_5__ {int imm; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ op; } ;
typedef  TYPE_2__ HexOp ;

/* Variables and functions */
 scalar_t__ HEX_OP_TYPE_IMM ; 
 int constant_extender ; 
 int /*<<< orphan*/  hex_op_extend (TYPE_2__*) ; 

void hex_op_extend_off(HexOp *op, int offset)
{
	if ((constant_extender != 1) && (op->type == HEX_OP_TYPE_IMM)) {
		op->op.imm = (op->op.imm) >> offset;
		hex_op_extend(op);
	}
}