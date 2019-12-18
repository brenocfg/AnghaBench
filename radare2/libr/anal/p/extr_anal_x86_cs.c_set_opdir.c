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
struct TYPE_5__ {int const type; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  direction; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 TYPE_3__ INSOP (int) ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_EXEC ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_READ ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_REF ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_WRITE ; 
#define  R_ANAL_OP_TYPE_CALL 135 
#define  R_ANAL_OP_TYPE_JMP 134 
#define  R_ANAL_OP_TYPE_LEA 133 
 int R_ANAL_OP_TYPE_MASK ; 
#define  R_ANAL_OP_TYPE_MOV 132 
#define  R_ANAL_OP_TYPE_UCALL 131 
#define  R_ANAL_OP_TYPE_UJMP 130 
#define  X86_OP_MEM 129 
#define  X86_OP_REG 128 

__attribute__((used)) static void set_opdir(RAnalOp *op, cs_insn *insn) {
	switch (op->type & R_ANAL_OP_TYPE_MASK) {
	case R_ANAL_OP_TYPE_MOV:
		switch (INSOP(0).type) {
		case X86_OP_MEM:
			op->direction = R_ANAL_OP_DIR_WRITE;
			break;
		case X86_OP_REG:
			if (INSOP(1).type == X86_OP_MEM) {
				op->direction = R_ANAL_OP_DIR_READ;
			}
			break;
		default:
			break;
		}
		break;
	case R_ANAL_OP_TYPE_LEA:
		op->direction = R_ANAL_OP_DIR_REF;
		break;
	case R_ANAL_OP_TYPE_CALL:
	case R_ANAL_OP_TYPE_JMP:
	case R_ANAL_OP_TYPE_UJMP:
	case R_ANAL_OP_TYPE_UCALL:
		op->direction = R_ANAL_OP_DIR_EXEC;
		break;
	default:
		break;
	}
}