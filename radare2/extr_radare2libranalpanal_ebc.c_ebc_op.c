#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ebc_command_t ;
struct TYPE_7__ {int jump; int fail; int ptr; int val; int size; void* type; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
#define  EBC_ADD 169 
#define  EBC_AND 168 
#define  EBC_BREAK 167 
#define  EBC_CALL 166 
#define  EBC_CMPEQ 165 
#define  EBC_CMPGTE 164 
#define  EBC_CMPIEQ 163 
#define  EBC_CMPIGTE 162 
#define  EBC_CMPILTE 161 
#define  EBC_CMPIUGTE 160 
#define  EBC_CMPIULTE 159 
#define  EBC_CMPLTE 158 
#define  EBC_CMPUGTE 157 
#define  EBC_CMPULTE 156 
#define  EBC_JMP 155 
#define  EBC_JMP8 154 
#define  EBC_MOVBD 153 
#define  EBC_MOVBW 152 
#define  EBC_MOVDD 151 
#define  EBC_MOVDW 150 
#define  EBC_MOVI 149 
#define  EBC_MOVIN 148 
#define  EBC_MOVND 147 
#define  EBC_MOVNW 146 
#define  EBC_MOVQD 145 
#define  EBC_MOVQQ 144 
#define  EBC_MOVQW 143 
#define  EBC_MOVREL 142 
#define  EBC_MOVSND 141 
#define  EBC_MOVSNW 140 
#define  EBC_MOVWD 139 
#define  EBC_MOVWW 138 
#define  EBC_MUL 137 
#define  EBC_NEG 136 
 int const EBC_OPCODE_MASK ; 
#define  EBC_OR 135 
#define  EBC_POP 134 
#define  EBC_PUSH 133 
#define  EBC_RET 132 
#define  EBC_SHL 131 
#define  EBC_SHR 130 
#define  EBC_SUB 129 
#define  EBC_XOR 128 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_POP ; 
 void* R_ANAL_OP_TYPE_PUSH ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  ebc_anal_call (TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  ebc_anal_jmp (TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  ebc_anal_jmp8 (TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int ebc_decode_command (int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ebc_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	int ret;
	ebc_command_t cmd;
	ut8 opcode = buf[0] & EBC_OPCODE_MASK;

	if (!op) {
		return 2;
	}

	memset(op, 0, sizeof (RAnalOp));
	op->addr = addr;
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;

	ret = op->size = ebc_decode_command(buf, &cmd);

	if (ret < 0) {
		return ret;
	}

	switch (opcode) {
	case EBC_JMP8:
		ebc_anal_jmp8(op, addr, buf);
		break;
	case EBC_JMP:
		ebc_anal_jmp(op, addr, buf);
		break;
	case EBC_MOVBW:
	case EBC_MOVWW:
	case EBC_MOVDW:
	case EBC_MOVQW:
	case EBC_MOVBD:
	case EBC_MOVWD:
	case EBC_MOVDD:
	case EBC_MOVQD:
	case EBC_MOVSNW:
	case EBC_MOVSND:
	case EBC_MOVQQ:
	case EBC_MOVNW:
	case EBC_MOVND:
	case EBC_MOVI:
	case EBC_MOVIN:
	case EBC_MOVREL:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case EBC_RET:
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	case EBC_CMPEQ:
	case EBC_CMPLTE:
	case EBC_CMPGTE:
	case EBC_CMPULTE:
	case EBC_CMPUGTE:
	case EBC_CMPIEQ:
	case EBC_CMPILTE:
	case EBC_CMPIGTE:
	case EBC_CMPIULTE:
	case EBC_CMPIUGTE:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case EBC_SHR:
		op->type = R_ANAL_OP_TYPE_SHR;
		break;
	case EBC_SHL:
		op->type = R_ANAL_OP_TYPE_SHL;
		break;
	case EBC_OR:
		op->type = R_ANAL_OP_TYPE_OR;
		break;
	case EBC_XOR:
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case EBC_MUL:
		op->type = R_ANAL_OP_TYPE_MUL;
		break;
	case EBC_PUSH:
		op->type = R_ANAL_OP_TYPE_PUSH;
		break;
	case EBC_POP:
		op->type = R_ANAL_OP_TYPE_POP;
		break;
	case EBC_AND:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case EBC_ADD:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case EBC_SUB:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case EBC_NEG:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case EBC_CALL:
		ebc_anal_call(op, addr, buf);
		break;
	case EBC_BREAK:
		op->type = R_ANAL_OP_TYPE_SWI;
		break;
	default:
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	}

	return ret;
}