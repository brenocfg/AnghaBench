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
typedef  int ut64 ;
struct TYPE_8__ {int size; } ;
typedef  TYPE_2__ cs_insn ;
struct TYPE_7__ {int disp; int scale; int /*<<< orphan*/  index; int /*<<< orphan*/  base; int /*<<< orphan*/  segment; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/  imm; TYPE_1__ mem; int /*<<< orphan*/  size; } ;
struct TYPE_9__ {int ptr; int disp; int stackptr; int /*<<< orphan*/  val; int /*<<< orphan*/  stackop; int /*<<< orphan*/  type; int /*<<< orphan*/  refptr; int /*<<< orphan*/  cycles; } ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  CYCLE_MEM ; 
 TYPE_6__ INSOP (int) ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_REG ; 
 int /*<<< orphan*/  R_ANAL_STACK_SET ; 
 void* UT64_MAX ; 
 int X86_OP_IMM ; 
#define  X86_OP_MEM 129 
#define  X86_OP_REG 128 
 int /*<<< orphan*/  X86_REG_EBP ; 
 int /*<<< orphan*/  X86_REG_INVALID ; 
 int /*<<< orphan*/  X86_REG_RBP ; 
 int /*<<< orphan*/  X86_REG_RIP ; 

__attribute__((used)) static void op0_memimmhandle(RAnalOp *op, cs_insn *insn, ut64 addr, int regsz) {
	op->ptr = UT64_MAX;
	switch (INSOP(0).type) {
	case X86_OP_MEM:
		op->cycles = CYCLE_MEM;
		op->disp = INSOP(0).mem.disp;
		if (!op->disp) {
			op->disp = UT64_MAX;
		}
		op->refptr = INSOP(0).size;
		if (INSOP(0).mem.base == X86_REG_RIP) {
			op->ptr = addr + insn->size + op->disp;
		} else if (INSOP(0).mem.base == X86_REG_RBP || INSOP(0).mem.base == X86_REG_EBP) {
			op->type |= R_ANAL_OP_TYPE_REG;
			op->stackop = R_ANAL_STACK_SET;
			op->stackptr = regsz;
		} else if (INSOP(0).mem.segment == X86_REG_INVALID && INSOP(0).mem.base == X86_REG_INVALID
			   && INSOP(0).mem.index == X86_REG_INVALID && INSOP(0).mem.scale == 1) { // [<addr>]
			op->ptr = op->disp;
			if (op->ptr < 0x1000) {
				op->ptr = UT64_MAX;
			}
		}
		if (INSOP(1).type == X86_OP_IMM) {
			op->val = INSOP(1).imm;
		}
		break;
	case X86_OP_REG:
		if (INSOP(1).type == X86_OP_IMM) {
		//	(INSOP(0).reg != X86_REG_RSP) && (INSOP(0).reg != X86_REG_ESP)) {
			op->val = INSOP(1).imm;
		}
		break;
	default:
		break;
	}
}