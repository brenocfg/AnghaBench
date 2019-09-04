#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut16 ;
struct v810_cmd {int size; int addr; int jump; int fail; int ptr; int val; int /*<<< orphan*/  esil; void* type; } ;
typedef  int /*<<< orphan*/  st8 ;
typedef  int st32 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  big_endian; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  struct v810_cmd RAnalOp ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int COND (int /*<<< orphan*/ ) ; 
 int DISP26 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DISP9 (int /*<<< orphan*/ ) ; 
 int IMM5 (int /*<<< orphan*/ ) ; 
 int OPCODE (int /*<<< orphan*/ ) ; 
 int REG1 (int /*<<< orphan*/ ) ; 
 int REG2 (int /*<<< orphan*/ ) ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_IO ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_NOT ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SAR ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  SEXT5 (int) ; 
#define  V810_ADD 189 
#define  V810_ADDI 188 
#define  V810_ADD_IMM5 187 
#define  V810_AND 186 
#define  V810_ANDI 185 
#define  V810_BCOND 184 
#define  V810_CMP 183 
#define  V810_CMP_IMM5 182 
#define  V810_COND_E 181 
#define  V810_COND_GE 180 
#define  V810_COND_GT 179 
#define  V810_COND_H 178 
#define  V810_COND_L 177 
#define  V810_COND_LE 176 
#define  V810_COND_LT 175 
#define  V810_COND_N 174 
#define  V810_COND_NE 173 
#define  V810_COND_NH 172 
#define  V810_COND_NL 171 
#define  V810_COND_NONE 170 
 int V810_COND_NOP ; 
#define  V810_COND_NV 169 
#define  V810_COND_P 168 
#define  V810_COND_V 167 
#define  V810_DIV 166 
#define  V810_DIVU 165 
 int V810_FLAG_CY ; 
 int V810_FLAG_OV ; 
 int V810_FLAG_S ; 
 int V810_FLAG_Z ; 
#define  V810_INB 164 
#define  V810_INH 163 
#define  V810_INW 162 
#define  V810_JAL 161 
#define  V810_JMP 160 
#define  V810_JR 159 
#define  V810_LDB 158 
#define  V810_LDH 157 
#define  V810_LDSR 156 
#define  V810_LDW 155 
#define  V810_MOV 154 
#define  V810_MOVEA 153 
#define  V810_MOVHI 152 
#define  V810_MOV_IMM5 151 
#define  V810_MUL 150 
#define  V810_MULU 149 
#define  V810_NOT 148 
#define  V810_OR 147 
#define  V810_ORI 146 
#define  V810_OUTB 145 
#define  V810_OUTH 144 
#define  V810_OUTW 143 
#define  V810_RETI 142 
#define  V810_SAR 141 
#define  V810_SAR_IMM5 140 
#define  V810_SHL 139 
#define  V810_SHL_IMM5 138 
#define  V810_SHR 137 
#define  V810_SHR_IMM5 136 
#define  V810_STB 135 
#define  V810_STH 134 
#define  V810_STSR 133 
#define  V810_STW 132 
#define  V810_SUB 131 
#define  V810_TRAP 130 
#define  V810_XOR 129 
#define  V810_XORI 128 
 int /*<<< orphan*/  clear_flags (struct v810_cmd*,int) ; 
 int /*<<< orphan*/  memset (struct v810_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_read_ble16 (int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  update_flags (struct v810_cmd*,int) ; 
 int v810_decode_command (int const*,int,struct v810_cmd*) ; 

__attribute__((used)) static int v810_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	int ret;
	ut8 opcode, reg1, reg2, imm5, cond;
	ut16 word1, word2 = 0;
	st32 jumpdisp;
	struct v810_cmd cmd;

	memset (&cmd, 0, sizeof(cmd));
	memset (op, 0, sizeof(RAnalOp));
	r_strbuf_init (&op->esil);
	r_strbuf_set (&op->esil, "");

	ret = op->size = v810_decode_command (buf, len, &cmd);
	if (ret <= 0) {
		return ret;
	}

	word1 = r_read_ble16 (buf, anal->big_endian);

	if (ret == 4) {
		word2 = r_read_ble16 (buf+2, anal->big_endian);
	}

	op->addr = addr;
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;

	opcode = OPCODE(word1);
	if (opcode >> 3 == 0x4) {
		opcode &= 0x20;
	}

	switch (opcode) {
	case V810_MOV:
		op->type = R_ANAL_OP_TYPE_MOV;
		r_strbuf_appendf (&op->esil, "r%u,r%u,=",
						 REG1(word1), REG2(word1));
		break;
	case V810_MOV_IMM5:
		op->type = R_ANAL_OP_TYPE_MOV;
		r_strbuf_appendf (&op->esil, "%d,r%u,=",
						  (st8)SEXT5(IMM5(word1)), REG2(word1));
		break;
	case V810_MOVHI:
		op->type = R_ANAL_OP_TYPE_MOV;
		r_strbuf_appendf (&op->esil, "16,%hu,<<,r%u,+,r%u,=",
						 word2, REG1(word1), REG2(word1));
		break;
	case V810_MOVEA:
		op->type = R_ANAL_OP_TYPE_MOV;
		r_strbuf_appendf (&op->esil, "%hd,r%u,+,r%u,=",
						 word2, REG1(word1), REG2(word1));
		break;
	case V810_LDSR:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case V810_STSR:
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case V810_NOT:
		op->type = R_ANAL_OP_TYPE_NOT;
		r_strbuf_appendf (&op->esil, "r%u,0xffffffff,^,r%u,=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_DIV:
	case V810_DIVU:
		op->type = R_ANAL_OP_TYPE_DIV;
		r_strbuf_appendf (&op->esil, "r%u,r%u,/=,r%u,r%u,%,r30,=",
						 REG1(word1), REG2(word1),
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_OV | V810_FLAG_S | V810_FLAG_Z);
		break;
	case V810_JMP:
		if (REG1 (word1) == 31) {
			op->type = R_ANAL_OP_TYPE_RET;
		} else {
			op->type = R_ANAL_OP_TYPE_UJMP;
		}
		r_strbuf_appendf (&op->esil, "r%u,pc,=",
						 REG1(word1));
		break;
	case V810_OR:
		op->type = R_ANAL_OP_TYPE_OR;
		r_strbuf_appendf (&op->esil, "r%u,r%u,|=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_ORI:
		op->type = R_ANAL_OP_TYPE_OR;
		r_strbuf_appendf (&op->esil, "%hu,r%u,|,r%u,=",
						 word2, REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_MUL:
	case V810_MULU:
		op->type = R_ANAL_OP_TYPE_MUL;
		r_strbuf_appendf (&op->esil, "r%u,r%u,*=,32,r%u,r%u,*,>>,r30,=",
						 REG1(word1), REG2(word1),
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_OV | V810_FLAG_S | V810_FLAG_Z);
		break;
	case V810_XOR:
		op->type = R_ANAL_OP_TYPE_XOR;
		r_strbuf_appendf (&op->esil, "r%u,r%u,^=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_XORI:
		op->type = R_ANAL_OP_TYPE_XOR;
		r_strbuf_appendf (&op->esil, "%hu,r%u,^,r%u,=",
						 word2, REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_AND:
		op->type = R_ANAL_OP_TYPE_AND;
		r_strbuf_appendf (&op->esil, "r%u,r%u,&=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_ANDI:
		op->type = R_ANAL_OP_TYPE_AND;
		r_strbuf_appendf (&op->esil, "%hu,r%u,&,r%u,=",
						 word2, REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV | V810_FLAG_S);
		break;
	case V810_CMP:
		op->type = R_ANAL_OP_TYPE_CMP;
		r_strbuf_appendf (&op->esil, "r%u,r%u,==",
						 REG1(word1), REG2(word1));
		update_flags (op, -1);
		break;
	case V810_CMP_IMM5:
		op->type = R_ANAL_OP_TYPE_CMP;
		r_strbuf_appendf (&op->esil, "%d,r%u,==",
						  (st8)SEXT5(IMM5(word1)), REG2(word1));
		update_flags (op, -1);
		break;
	case V810_SUB:
		op->type = R_ANAL_OP_TYPE_SUB;
		r_strbuf_appendf (&op->esil, "r%u,r%u,-=",
						 REG1(word1), REG2(word1));
		update_flags (op, -1);
		break;
	case V810_ADD:
		op->type = R_ANAL_OP_TYPE_ADD;
		r_strbuf_appendf (&op->esil, "r%u,r%u,+=",
						 REG1(word1), REG2(word1));
		update_flags (op, -1);
		break;
	case V810_ADDI:
		op->type = R_ANAL_OP_TYPE_ADD;
		r_strbuf_appendf (&op->esil, "%hd,r%u,+,r%u,=",
						 word2, REG1(word1), REG2(word1));
		update_flags (op, -1);
		break;
	case V810_ADD_IMM5:
		op->type = R_ANAL_OP_TYPE_ADD;
		r_strbuf_appendf (&op->esil, "%d,r%u,+=",
						  (st8)SEXT5(IMM5(word1)), REG2(word1));
		update_flags(op, -1);
		break;
	case V810_SHR:
		op->type = R_ANAL_OP_TYPE_SHR;
		r_strbuf_appendf (&op->esil, "r%u,r%u,>>=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_SHR_IMM5:
		op->type = R_ANAL_OP_TYPE_SHR;
		r_strbuf_appendf (&op->esil, "%u,r%u,>>=",
						  (ut8)IMM5(word1), REG2(word1));
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_SAR:
		op->type = R_ANAL_OP_TYPE_SAR;
		reg1 = REG1(word1);
		reg2 = REG2(word1);
		r_strbuf_appendf (&op->esil, "31,r%u,>>,?{,r%u,32,-,r%u,1,<<,--,<<,}{,0,},r%u,r%u,>>,|,r%u,=",
						 reg2, reg1, reg1, reg1, reg2, reg2);
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_SAR_IMM5:
		op->type = R_ANAL_OP_TYPE_SAR;
		imm5 = IMM5(word1);
		reg2 = REG2(word1);
		r_strbuf_appendf (&op->esil, "31,r%u,>>,?{,%u,32,-,%u,1,<<,--,<<,}{,0,},%u,r%u,>>,|,r%u,=",
						  reg2, (ut8)imm5, (ut8)imm5, (ut8)imm5, reg2, reg2);
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_SHL:
		op->type = R_ANAL_OP_TYPE_SHL;
		r_strbuf_appendf (&op->esil, "r%u,r%u,<<=",
						 REG1(word1), REG2(word1));
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_SHL_IMM5:
		op->type = R_ANAL_OP_TYPE_SHL;
		r_strbuf_appendf (&op->esil, "%u,r%u,<<=",
						  (ut8)IMM5(word1), REG2(word1));
		update_flags (op, V810_FLAG_CY | V810_FLAG_S | V810_FLAG_Z);
		clear_flags (op, V810_FLAG_OV);
		break;
	case V810_LDB:
		op->type = R_ANAL_OP_TYPE_LOAD;
		r_strbuf_appendf (&op->esil, "r%u,%hd,+,[1],r%u,=",
						 REG1(word1), word2, REG2(word1));
		r_strbuf_appendf (&op->esil, ",DUP,0x80,&,?{,0xffffff00,|,}");
		break;
	case V810_LDH:
		op->type = R_ANAL_OP_TYPE_LOAD;
		r_strbuf_appendf (&op->esil, "r%u,%hd,+,0xfffffffe,&,[2],r%u,=",
						 REG1(word1), word2, REG2(word1));
		r_strbuf_appendf (&op->esil, ",DUP,0x8000,&,?{,0xffffff00,|,}");
		break;
	case V810_LDW:
		op->type = R_ANAL_OP_TYPE_LOAD;
		r_strbuf_appendf (&op->esil, "r%u,%hd,+,0xfffffffc,&,[4],r%u,=",
						 REG1(word1), word2, REG2(word1));
		r_strbuf_appendf (&op->esil, ",DUP,0x80000000,&,?{,0xffffff00,|,}");
		break;
	case V810_STB:
		op->type = R_ANAL_OP_TYPE_STORE;
		r_strbuf_appendf (&op->esil, "r%u,r%u,%hd,+,=[1]",
						 REG2(word1), REG1(word1), word2);
		break;
	case V810_STH:
		op->type = R_ANAL_OP_TYPE_STORE;
		r_strbuf_appendf (&op->esil, "r%u,r%u,%hd,+,0xfffffffe,&,=[2]",
						 REG2(word1), REG1(word1), word2);
		break;
	case V810_STW:
		op->type = R_ANAL_OP_TYPE_STORE;
		r_strbuf_appendf (&op->esil, "r%u,r%u,%hd,+,=[4]",
						 REG2(word1), REG1(word1), word2);
		break;
	case V810_INB:
	case V810_INH:
	case V810_INW:
	case V810_OUTB:
	case V810_OUTH:
	case V810_OUTW:
		op->type = R_ANAL_OP_TYPE_IO;
		break;
	case V810_TRAP:
		op->type = R_ANAL_OP_TYPE_TRAP;
		r_strbuf_appendf (&op->esil, "%u,TRAP", IMM5(word1));
		break;
	case V810_RETI:
		op->type = R_ANAL_OP_TYPE_RET;
		//r_strbuf_appendf (&op->esil, "np,?{,fepc,fepsw,}{,eipc,eipsw,},psw,=,pc,=");
		break;
	case V810_JAL:
	case V810_JR:
		jumpdisp = DISP26(word1, word2);
		op->jump = addr + jumpdisp;
		op->fail = addr + 4;

		if (opcode == V810_JAL) {
			op->type = R_ANAL_OP_TYPE_CALL;
			r_strbuf_appendf (&op->esil, "$$,4,+,r31,=,", jumpdisp);
		} else {
			op->type = R_ANAL_OP_TYPE_JMP;
		}

		r_strbuf_appendf (&op->esil, "$$,%d,+,pc,=", jumpdisp);
		break;
	case V810_BCOND:
		cond = COND(word1);
		if (cond == V810_COND_NOP) {
			op->type = R_ANAL_OP_TYPE_NOP;
			break;
		}

		jumpdisp = DISP9(word1);
		op->jump = addr + jumpdisp;
		op->fail = addr + 2;
		op->type = R_ANAL_OP_TYPE_CJMP;

		switch (cond) {
		case V810_COND_V:
			r_strbuf_appendf (&op->esil, "ov");
			break;
		case V810_COND_L:
			r_strbuf_appendf (&op->esil, "cy");
			break;
		case V810_COND_E:
			r_strbuf_appendf (&op->esil, "z");
			break;
		case V810_COND_NH:
			r_strbuf_appendf (&op->esil, "cy,z,|");
			break;
		case V810_COND_N:
			r_strbuf_appendf (&op->esil, "s");
			break;
		case V810_COND_NONE:
			r_strbuf_appendf (&op->esil, "1");
			break;
		case V810_COND_LT:
			r_strbuf_appendf (&op->esil, "s,ov,^");
			break;
		case V810_COND_LE:
			r_strbuf_appendf (&op->esil, "s,ov,^,z,|");
			break;
		case V810_COND_NV:
			r_strbuf_appendf (&op->esil, "ov,!");
			break;
		case V810_COND_NL:
			r_strbuf_appendf (&op->esil, "cy,!");
			break;
		case V810_COND_NE:
			r_strbuf_appendf (&op->esil, "z,!");
			break;
		case V810_COND_H:
			r_strbuf_appendf (&op->esil, "cy,z,|,!");
			break;
		case V810_COND_P:
			r_strbuf_appendf (&op->esil, "s,!");
			break;
		case V810_COND_GE:
			r_strbuf_appendf (&op->esil, "s,ov,^,!");
			break;
		case V810_COND_GT:
			r_strbuf_appendf (&op->esil, "s,ov,^,z,|,!");
			break;
		}
		r_strbuf_appendf (&op->esil, ",?{,$$,%d,+,pc,=,}", jumpdisp);
		break;
	}

	return ret;
}