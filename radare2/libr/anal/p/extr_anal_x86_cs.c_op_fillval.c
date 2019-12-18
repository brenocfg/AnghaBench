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
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_4__ {int type; int /*<<< orphan*/ * src; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SRC_DST (TYPE_1__*) ; 
#define  R_ANAL_OP_TYPE_ACMP 147 
#define  R_ANAL_OP_TYPE_ADD 146 
#define  R_ANAL_OP_TYPE_AND 145 
#define  R_ANAL_OP_TYPE_CMOV 144 
#define  R_ANAL_OP_TYPE_CMP 143 
#define  R_ANAL_OP_TYPE_LEA 142 
 int R_ANAL_OP_TYPE_MASK ; 
#define  R_ANAL_OP_TYPE_MOV 141 
#define  R_ANAL_OP_TYPE_NOT 140 
#define  R_ANAL_OP_TYPE_OR 139 
#define  R_ANAL_OP_TYPE_POP 138 
 int R_ANAL_OP_TYPE_REG ; 
#define  R_ANAL_OP_TYPE_ROL 137 
#define  R_ANAL_OP_TYPE_ROR 136 
#define  R_ANAL_OP_TYPE_SAL 135 
#define  R_ANAL_OP_TYPE_SAR 134 
#define  R_ANAL_OP_TYPE_SHL 133 
#define  R_ANAL_OP_TYPE_SHR 132 
#define  R_ANAL_OP_TYPE_SUB 131 
#define  R_ANAL_OP_TYPE_UPUSH 130 
#define  R_ANAL_OP_TYPE_XCHG 129 
#define  R_ANAL_OP_TYPE_XOR 128 
 int /*<<< orphan*/  set_src_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void op_fillval(RAnal *a, RAnalOp *op, csh *handle, cs_insn *insn) {
	switch (op->type & R_ANAL_OP_TYPE_MASK) {
	case R_ANAL_OP_TYPE_MOV:
	case R_ANAL_OP_TYPE_CMP:
	case R_ANAL_OP_TYPE_LEA:
	case R_ANAL_OP_TYPE_CMOV:
	case R_ANAL_OP_TYPE_SHL:
	case R_ANAL_OP_TYPE_SHR:
	case R_ANAL_OP_TYPE_SAL:
	case R_ANAL_OP_TYPE_SAR:
	case R_ANAL_OP_TYPE_ROL:
	case R_ANAL_OP_TYPE_ROR:
	case R_ANAL_OP_TYPE_ADD:
	case R_ANAL_OP_TYPE_AND:
	case R_ANAL_OP_TYPE_OR:
	case R_ANAL_OP_TYPE_XOR:
	case R_ANAL_OP_TYPE_SUB:
	case R_ANAL_OP_TYPE_XCHG:
	case R_ANAL_OP_TYPE_POP:
	case R_ANAL_OP_TYPE_NOT:
	case R_ANAL_OP_TYPE_ACMP:
		CREATE_SRC_DST (op);
		set_src_dst (op->dst, handle, insn, 0);
		set_src_dst (op->src[0], handle, insn, 1);
		set_src_dst (op->src[1], handle, insn, 2);
		set_src_dst (op->src[2], handle, insn, 3);
		break;
	case R_ANAL_OP_TYPE_UPUSH:
		if ((op->type & R_ANAL_OP_TYPE_REG)) {
			CREATE_SRC_DST (op);
			set_src_dst (op->src[0], handle, insn, 0);
		}
		break;
	default:
		break;
	}
}