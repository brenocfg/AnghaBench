#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ reg; int /*<<< orphan*/  imm; } ;
struct TYPE_4__ {int /*<<< orphan*/  stackptr; int /*<<< orphan*/  stackop; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 TYPE_3__ INSOP (int) ; 
 int /*<<< orphan*/  R_ANAL_STACK_INC ; 
 scalar_t__ X86_OP_IMM ; 
 scalar_t__ X86_OP_REG ; 
 scalar_t__ X86_REG_ESP ; 
 scalar_t__ X86_REG_RSP ; 

__attribute__((used)) static void op_stackidx(RAnalOp *op, cs_insn *insn, bool minus) {
	if (INSOP(0).type == X86_OP_REG && INSOP(1).type == X86_OP_IMM) {
		if (INSOP(0).reg == X86_REG_RSP || INSOP(0).reg == X86_REG_ESP) {
			op->stackop = R_ANAL_STACK_INC;
			if (minus) {
				op->stackptr = -INSOP(1).imm;
			} else {
				op->stackptr = INSOP(1).imm;
			}
		}
	}
}