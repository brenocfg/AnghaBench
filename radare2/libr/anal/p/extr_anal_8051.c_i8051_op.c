#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_12__ {int const op; int const mask; int arg1; int arg2; int len; int instr; int /*<<< orphan*/  type; int /*<<< orphan*/  cycles; scalar_t__ string; } ;
struct TYPE_11__ {int /*<<< orphan*/  reg; } ;
struct TYPE_10__ {int jump; int fail; int ptr; int val; int nopcode; int size; int id; int eob; int stackptr; int refptr; int /*<<< orphan*/  mnemonic; void* stackop; int /*<<< orphan*/  cond; int /*<<< orphan*/  family; int /*<<< orphan*/  type; int /*<<< orphan*/  failcycles; int /*<<< orphan*/  cycles; scalar_t__ delay; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int A_ADDR11 ; 
 int A_ADDR16 ; 
#define  A_BIT 145 
#define  A_DIRECT 144 
#define  A_IMM16 143 
#define  A_IMMEDIATE 142 
 int A_OFFSET ; 
 int A_RI ; 
 int A_RN ; 
#define  OP_CALL 141 
#define  OP_CJNE 140 
#define  OP_DJNZ 139 
#define  OP_JB 138 
#define  OP_JBC 137 
#define  OP_JC 136 
#define  OP_JMP 135 
#define  OP_JNB 134 
#define  OP_JNC 133 
#define  OP_JNZ 132 
#define  OP_JZ 131 
#define  OP_POP 130 
#define  OP_PUSH 129 
#define  OP_RET 128 
 int /*<<< orphan*/  R_ANAL_COND_AL ; 
 int /*<<< orphan*/  R_ANAL_COND_EQ ; 
 int /*<<< orphan*/  R_ANAL_COND_HS ; 
 int /*<<< orphan*/  R_ANAL_COND_LO ; 
 int /*<<< orphan*/  R_ANAL_COND_NE ; 
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_CPU ; 
 int R_ANAL_OP_MASK_ESIL ; 
 int R_ANAL_OP_MASK_HINT ; 
 void* R_ANAL_STACK_INC ; 
 TYPE_9__* _8051_ops ; 
 int /*<<< orphan*/  analop_esil (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 void* arg_addr11 (int /*<<< orphan*/ ,int const*) ; 
 int const arg_bit (int const) ; 
 void* arg_offset (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  i8051_reg_read (int /*<<< orphan*/ ,char*) ; 
 void* map_direct_addr (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  r_8051_disas (int /*<<< orphan*/ ,int const*,int,int*) ; 
 int /*<<< orphan*/  set_cpu_model (TYPE_2__*,int) ; 

__attribute__((used)) static int i8051_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	set_cpu_model (anal, false);

	int i = 0;
	while (_8051_ops[i].string && _8051_ops[i].op != (buf[0] & ~_8051_ops[i].mask))	{
		i++;
	}

	op->jump = op->fail = -1;
	op->ptr = op->val = -1;

	ut8 arg1 = _8051_ops[i].arg1;
	ut8 arg2 = _8051_ops[i].arg2;

	op->delay = 0;
	op->cycles = _8051_ops[i].cycles;
	op->failcycles = _8051_ops[i].cycles;
	op->nopcode = 1;
	op->size = _8051_ops[i].len;
	op->type = _8051_ops[i].type;
	op->family = R_ANAL_OP_FAMILY_CPU; // maybe also FAMILY_IO...
	op->id = i;

	switch (_8051_ops[i].instr) {
	default:
		op->cond = R_ANAL_COND_AL;
	break;
	case OP_CJNE:
	case OP_DJNZ:
	case OP_JB:
	case OP_JBC:
	case OP_JNZ:
		op->cond = R_ANAL_COND_NE;
	break;
	case OP_JNB:
	case OP_JZ:
		op->cond = R_ANAL_COND_EQ;
	break; case OP_JC:
		op->cond = R_ANAL_COND_HS;
	break; case OP_JNC:
		op->cond = R_ANAL_COND_LO;
	}

	switch (_8051_ops[i].instr) {
	default:
		op->eob = false;
	break;
	case OP_CJNE:
	case OP_DJNZ:
	case OP_JB:
	case OP_JBC:
	case OP_JC:
	case OP_JMP:
	case OP_JNB:
	case OP_JNC:
	case OP_JNZ:
	case OP_JZ:
		op->eob = true;
	}

	// TODO: op->datatype

	switch (arg1) {
	default:
	break; case A_DIRECT:
		op->ptr = map_direct_addr (anal, buf[1]);
	break; case A_BIT:
		op->ptr = map_direct_addr (anal, arg_bit (buf[1]));
	break; case A_IMMEDIATE:
		op->val = buf[1];
	break; case A_IMM16:
		op->val = buf[1] * 256 + buf[2];
		op->ptr = op->val + i8051_reg_read (anal->reg, "_xdata"); // best guess, it's a XRAM pointer
	}

	switch (arg2) {
	default:
	break; case A_DIRECT:
		if (arg1 == A_RI || arg1 == A_RN) {
			op->ptr = map_direct_addr (anal, buf[1]);
		} else if (arg1 != A_DIRECT) {
			op->ptr = map_direct_addr (anal, buf[2]);
		}
	break; case A_BIT:
		op->ptr = arg_bit ((arg1 == A_RI || arg1 == A_RN) ? buf[1] : buf[2]);
		op->ptr = map_direct_addr (anal, op->ptr);
	break; case A_IMMEDIATE:
		op->val = (arg1 == A_RI || arg1 == A_RN) ? buf[1] : buf[2];
	}

	switch(_8051_ops[i].instr) {
	default:
	break; case OP_PUSH:
		op->stackop = R_ANAL_STACK_INC;
		op->stackptr = 1;
	break; case OP_POP:
		op->stackop = R_ANAL_STACK_INC;
		op->stackptr = -1;
	break; case OP_RET:
		op->stackop = R_ANAL_STACK_INC;
		op->stackptr = -2;
	break; case OP_CALL:
		op->stackop = R_ANAL_STACK_INC;
		op->stackptr = 2;
		if (arg1 == A_ADDR11) {
			op->jump = arg_addr11 (addr + op->size, buf);
			op->fail = addr + op->size;
		} else if (arg1 == A_ADDR16) {
			op->jump = 0x100 * buf[1] + buf[2];
			op->fail = addr + op->size;
		}
	break; case OP_JMP:
		if (arg1 == A_ADDR11) {
			op->jump = arg_addr11 (addr + op->size, buf);
			op->fail = addr + op->size;
		} else if (arg1 == A_ADDR16) {
			op->jump = 0x100 * buf[1] + buf[2];
			op->fail = addr + op->size;
		} else if (arg1 == A_OFFSET) {
			op->jump = arg_offset (addr + op->size, buf[1]);
			op->fail = addr + op->size;
		}
	break;
	case OP_CJNE:
	case OP_DJNZ:
	case OP_JC:
	case OP_JNC:
	case OP_JZ:
	case OP_JNZ:
	case OP_JB:
	case OP_JBC:
	case OP_JNB:
		op->jump = arg_offset (addr + op->size, buf[op->size - 1]);
		op->fail = addr + op->size;
	}

	if (op->ptr != -1 && op->refptr == 0) {
		op->refptr = 1;
	}

	if (mask & R_ANAL_OP_MASK_ESIL) {
		ut8 copy[3] = {0, 0, 0};
		memcpy (copy, buf, len >= 3 ? 3 : len);
		analop_esil (anal, op, addr, copy);
	}

	int olen = 0;
	op->mnemonic = r_8051_disas (addr, buf, len, &olen);
	op->size = olen;

	if (mask & R_ANAL_OP_MASK_HINT) {
		// TODO: op->hint
	}

	return op->size;
}