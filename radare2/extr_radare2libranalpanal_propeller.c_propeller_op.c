#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct propeller_cmd {int size; int ptr; int val; int opcode; int dst; int src; int /*<<< orphan*/  type; int /*<<< orphan*/  fail; int /*<<< orphan*/  jump; int /*<<< orphan*/  immed; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  struct propeller_cmd RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
#define  PROP_ABS 162 
#define  PROP_ADD 161 
#define  PROP_ADDABS 160 
#define  PROP_ADDX 159 
#define  PROP_CMPS 158 
#define  PROP_CMPSUB 157 
#define  PROP_DJNZ 156 
#define  PROP_JMP 155 
#define  PROP_MAX 154 
#define  PROP_MAXS 153 
#define  PROP_MIN 152 
#define  PROP_MINS 151 
#define  PROP_MOV 150 
#define  PROP_MOVD 149 
#define  PROP_MOVI 148 
#define  PROP_MOVS 147 
#define  PROP_MUXC 146 
#define  PROP_NEG 145 
#define  PROP_OR 144 
#define  PROP_RCL 143 
#define  PROP_RCR 142 
#define  PROP_RDBYTE 141 
#define  PROP_RDLONG 140 
#define  PROP_RDWORD 139 
#define  PROP_ROL 138 
#define  PROP_ROR 137 
#define  PROP_SHL 136 
#define  PROP_SHR 135 
#define  PROP_SUB 134 
#define  PROP_TEST 133 
#define  PROP_TESTN 132 
#define  PROP_TJNZ 131 
#define  PROP_TJZ 130 
#define  PROP_WAITVID 129 
#define  PROP_XOR 128 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ADD ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_AND ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_MOV ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_OR ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_RET ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ROL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ROR ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_SUB ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UNK ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  memset (struct propeller_cmd*,int /*<<< orphan*/ ,int) ; 
 int propeller_decode_command (int /*<<< orphan*/  const*,struct propeller_cmd*) ; 

__attribute__((used)) static int propeller_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	int ret;
	struct propeller_cmd cmd;

	memset (&cmd, 0, sizeof (cmd));
	memset (op, 0, sizeof (RAnalOp));

	ret = op->size = propeller_decode_command (buf, &cmd);

	if (ret < 0) {
		return ret;
	}

	op->addr = addr;
	op->jump = op->fail = UT64_MAX;
	op->ptr = op->val = -1;

	switch (cmd.opcode) {
	case PROP_TEST:
	case PROP_TESTN:
	case PROP_TJNZ:
	case PROP_TJZ:
	case PROP_CMPS:
	case PROP_CMPSUB:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case PROP_ADD:
	case PROP_ADDX:
	case PROP_ADDABS:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case PROP_OR:
		op->type = R_ANAL_OP_TYPE_OR;
		break;
	case PROP_RCL:
	case PROP_ROL:
	case PROP_SHL:
		op->type = R_ANAL_OP_TYPE_ROL;
		break;
	case PROP_RCR:
	case PROP_ROR:
	case PROP_SHR:
		op->type = R_ANAL_OP_TYPE_ROR;
		break;
	case PROP_NEG:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case PROP_XOR:
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case PROP_ABS:
	case PROP_MINS:
	case PROP_MIN:
	case PROP_MAX:
	case PROP_MAXS:
	case PROP_RDBYTE:
	case PROP_RDLONG:
	case PROP_RDWORD:
	case PROP_MOV:
	case PROP_MOVD:
	case PROP_MOVI:
	case PROP_MOVS:
	case PROP_WAITVID:
	case PROP_MUXC:
		if (cmd.opcode == PROP_MOV && cmd.dst == 0x44 && cmd.src == 0x3c) {
			op->type = R_ANAL_OP_TYPE_RET;
		} else {
			op->type = R_ANAL_OP_TYPE_MOV;
		}
		break;
	case PROP_SUB:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case PROP_JMP:
	case PROP_DJNZ:
		if (cmd.immed == 0) {
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = 0x20 + cmd.src;
			op->fail = addr + 2;
		} else {
			op->type = R_ANAL_OP_TYPE_UJMP;
			op->fail = addr + 2;
		}
		break;
	default:
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	}

	return ret;
}