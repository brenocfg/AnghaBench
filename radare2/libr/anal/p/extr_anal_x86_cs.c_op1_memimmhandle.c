#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_8__ {scalar_t__ size; } ;
typedef  TYPE_2__ cs_insn ;
struct TYPE_7__ {scalar_t__ disp; int scale; int /*<<< orphan*/  index; int /*<<< orphan*/  base; int /*<<< orphan*/  segment; } ;
struct TYPE_10__ {int type; int size; int imm; int /*<<< orphan*/  reg; TYPE_1__ mem; } ;
struct TYPE_9__ {int refptr; scalar_t__ ptr; scalar_t__ disp; int stackptr; int /*<<< orphan*/  stackop; } ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 TYPE_6__ INSOP (int) ; 
 int /*<<< orphan*/  R_ANAL_STACK_GET ; 
 scalar_t__ UT64_MAX ; 
#define  X86_OP_IMM 129 
#define  X86_OP_MEM 128 
 int /*<<< orphan*/  X86_REG_EBP ; 
 int /*<<< orphan*/  X86_REG_ESP ; 
 int /*<<< orphan*/  X86_REG_INVALID ; 
 int /*<<< orphan*/  X86_REG_RBP ; 
 int /*<<< orphan*/  X86_REG_RIP ; 
 int /*<<< orphan*/  X86_REG_RSP ; 

__attribute__((used)) static void op1_memimmhandle(RAnalOp *op, cs_insn *insn, ut64 addr, int regsz) {
	if (op->refptr < 1 || op->ptr == UT64_MAX) {
		switch (INSOP(1).type) {
		case X86_OP_MEM:
			op->disp = INSOP(1).mem.disp;
			op->refptr = INSOP(1).size;
			if (INSOP(1).mem.base == X86_REG_RIP) {
				op->ptr = addr + insn->size + op->disp;
			} else if (INSOP(1).mem.base == X86_REG_RBP || INSOP(1).mem.base == X86_REG_EBP) {
				op->stackop = R_ANAL_STACK_GET;
				op->stackptr = regsz;
			} else if (INSOP(1).mem.segment == X86_REG_INVALID && INSOP(1).mem.base == X86_REG_INVALID
			           && INSOP(1).mem.index == X86_REG_INVALID && INSOP(1).mem.scale == 1) { // [<addr>]
				op->ptr = op->disp;
			}
			break;
		case X86_OP_IMM:
			if ((INSOP (1).imm > 10) &&
				(INSOP(0).reg != X86_REG_RSP) && (INSOP(0).reg != X86_REG_ESP)) {
				op->ptr = INSOP (1).imm;
			}
			break;
		default:
			break;
		}
	}
}