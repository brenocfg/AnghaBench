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
struct h8300_cmd {int dummy; } ;
typedef  int st8 ;
struct TYPE_7__ {int jump; int fail; int ptr; int val; int size; scalar_t__ type; int /*<<< orphan*/  addr; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
#define  H8300_ADDB_DIRECT 190 
#define  H8300_ADDS 189 
#define  H8300_ADDW_DIRECT 188 
#define  H8300_ADDX 187 
#define  H8300_ADDX_4BIT 186 
#define  H8300_ADD_4BIT 185 
#define  H8300_ANDC 184 
#define  H8300_AND_4BIT 183 
#define  H8300_BCC 182 
#define  H8300_BCS 181 
#define  H8300_BEQ 180 
#define  H8300_BGE 179 
#define  H8300_BGT 178 
#define  H8300_BHI 177 
#define  H8300_BLE 176 
#define  H8300_BLS 175 
#define  H8300_BLT 174 
#define  H8300_BMI 173 
#define  H8300_BNE 172 
#define  H8300_BPL 171 
#define  H8300_BRA 170 
#define  H8300_BRN 169 
#define  H8300_BTST 168 
#define  H8300_BTST_R2R8 167 
#define  H8300_BVC 166 
#define  H8300_BVS 165 
#define  H8300_CMP_1 164 
#define  H8300_CMP_2 163 
#define  H8300_CMP_4BIT 162 
#define  H8300_EEPMOV 161 
#define  H8300_JMP_1 160 
#define  H8300_JMP_2 159 
#define  H8300_JMP_3 158 
#define  H8300_JSR_1 157 
#define  H8300_JSR_2 156 
#define  H8300_JSR_3 155 
#define  H8300_MOV_1 154 
#define  H8300_MOV_2 153 
#define  H8300_MOV_4BIT 152 
#define  H8300_MOV_4BIT_2 151 
#define  H8300_MOV_4BIT_3 150 
#define  H8300_MOV_ABS162R16 149 
#define  H8300_MOV_DISP162R16 148 
#define  H8300_MOV_IMM162R16 147 
#define  H8300_MOV_IND162R16 146 
#define  H8300_MOV_INDINC162R16 145 
#define  H8300_MOV_R82ABS16 144 
#define  H8300_MOV_R82DISPR16 143 
#define  H8300_MOV_R82IND16 142 
#define  H8300_MOV_R82RDEC16 141 
#define  H8300_MULXU 140 
#define  H8300_NOP 139 
#define  H8300_RTS 138 
#define  H8300_SHL 137 
#define  H8300_SHR 136 
#define  H8300_SUBS 135 
#define  H8300_SUBW 134 
#define  H8300_SUBX 133 
#define  H8300_SUBX_4BIT 132 
#define  H8300_SUB_1 131 
#define  H8300_XOR 130 
#define  H8300_XORC 129 
#define  H8300_XOR_4BIT 128 
 int R_ANAL_OP_MASK_ESIL ; 
 scalar_t__ R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 scalar_t__ R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 scalar_t__ R_ANAL_OP_TYPE_MUL ; 
 scalar_t__ R_ANAL_OP_TYPE_NOP ; 
 scalar_t__ R_ANAL_OP_TYPE_RET ; 
 scalar_t__ R_ANAL_OP_TYPE_SHL ; 
 scalar_t__ R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 scalar_t__ R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  analop_esil (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  h8300_anal_jmp (TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  h8300_anal_jsr (TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int h8300_decode_command (int const*,struct h8300_cmd*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int h8300_op(RAnal *anal, RAnalOp *op, ut64 addr,
		const ut8 *buf, int len, RAnalOpMask mask)
{
	int ret;
	ut8 opcode = buf[0];
	struct h8300_cmd cmd;

	if (!op) {
		return 2;
	}

	memset(op, 0, sizeof (RAnalOp));

	op->addr = addr;
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;
	ret = op->size = h8300_decode_command(buf, &cmd);

	if (ret < 0) {
		return ret;
	}
	switch (opcode >> 4) {
	case H8300_MOV_4BIT_2:
	case H8300_MOV_4BIT_3:
	case H8300_MOV_4BIT:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case H8300_CMP_4BIT:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case H8300_XOR_4BIT:
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case H8300_AND_4BIT:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case H8300_ADD_4BIT:
	case H8300_ADDX_4BIT:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case H8300_SUBX_4BIT:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	default:
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	};

	if (op->type != R_ANAL_OP_TYPE_UNK) {
		analop_esil(anal, op, addr, buf);
		return ret;
	}
	switch (opcode) {
	case H8300_MOV_R82IND16:
	case H8300_MOV_IND162R16:
	case H8300_MOV_R82ABS16:
	case H8300_MOV_ABS162R16:
	case H8300_MOV_R82RDEC16:
	case H8300_MOV_INDINC162R16:
	case H8300_MOV_R82DISPR16:
	case H8300_MOV_DISP162R16:
	case H8300_MOV_IMM162R16:
	case H8300_MOV_1:
	case H8300_MOV_2:
	case H8300_EEPMOV:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case H8300_RTS:
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	case H8300_CMP_1:
	case H8300_CMP_2:
	case H8300_BTST_R2R8:
	case H8300_BTST:
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case H8300_SHL:
		op->type = R_ANAL_OP_TYPE_SHL;
		break;
	case H8300_SHR:
		op->type = R_ANAL_OP_TYPE_SHR;
		break;
	case H8300_XOR:
	case H8300_XORC:
		op->type = R_ANAL_OP_TYPE_XOR;
		break;
	case H8300_MULXU:
		op->type = R_ANAL_OP_TYPE_MUL;
		break;
	case H8300_ANDC:
		op->type = R_ANAL_OP_TYPE_AND;
		break;
	case H8300_ADDB_DIRECT:
	case H8300_ADDW_DIRECT:
	case H8300_ADDS:
	case H8300_ADDX:
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case H8300_SUB_1:
	case H8300_SUBW:
	case H8300_SUBS:
	case H8300_SUBX:
		op->type = R_ANAL_OP_TYPE_SUB;
		break;
	case H8300_NOP:
		op->type = R_ANAL_OP_TYPE_NOP;
		break;
	case H8300_JSR_1:
	case H8300_JSR_2:
	case H8300_JSR_3:
		h8300_anal_jsr(op, addr, buf);
		break;
	case H8300_JMP_1:
	case H8300_JMP_2:
	case H8300_JMP_3:
		h8300_anal_jmp(op, addr, buf);
		break;
	case H8300_BRA:
	case H8300_BRN:
	case H8300_BHI:
	case H8300_BLS:
	case H8300_BCC:
	case H8300_BCS:
	case H8300_BNE:
	case H8300_BEQ:
	case H8300_BVC:
	case H8300_BVS:
	case H8300_BPL:
	case H8300_BMI:
	case H8300_BGE:
	case H8300_BLT:
	case H8300_BGT:
	case H8300_BLE:
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = addr + 2 + (st8)(buf[1]);
		op->fail = addr + 2;
		break;
	default:
		op->type = R_ANAL_OP_TYPE_UNK;
		break;
	};
	if (mask & R_ANAL_OP_MASK_ESIL) {
		analop_esil(anal, op, addr, buf);
	}
	return ret;
}