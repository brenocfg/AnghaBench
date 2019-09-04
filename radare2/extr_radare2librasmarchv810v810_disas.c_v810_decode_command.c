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
typedef  int /*<<< orphan*/  ut16 ;
struct v810_cmd {int dummy; } ;

/* Variables and functions */
 int OPCODE (int /*<<< orphan*/ ) ; 
#define  V810_ADD 180 
#define  V810_ADDI 179 
#define  V810_ADD_IMM5 178 
#define  V810_AND 177 
#define  V810_ANDI 176 
#define  V810_BSTR 175 
#define  V810_CAXI 174 
#define  V810_CLI 173 
#define  V810_CMP 172 
#define  V810_CMP_IMM5 171 
#define  V810_DIV 170 
#define  V810_DIVU 169 
#define  V810_EXT 168 
#define  V810_HALT 167 
#define  V810_INB 166 
#define  V810_INH 165 
#define  V810_INW 164 
#define  V810_JAL 163 
#define  V810_JMP 162 
#define  V810_JR 161 
#define  V810_LDB 160 
#define  V810_LDH 159 
#define  V810_LDSR 158 
#define  V810_LDW 157 
#define  V810_MOV 156 
#define  V810_MOVEA 155 
#define  V810_MOVHI 154 
#define  V810_MOV_IMM5 153 
#define  V810_MUL 152 
#define  V810_MULU 151 
#define  V810_NOT 150 
#define  V810_OR 149 
#define  V810_ORI 148 
#define  V810_OUTB 147 
#define  V810_OUTH 146 
#define  V810_OUTW 145 
#define  V810_RETI 144 
#define  V810_SAR 143 
#define  V810_SAR_IMM5 142 
#define  V810_SEI 141 
#define  V810_SETF 140 
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
 int decode_3operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_bcond (int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_bit_op (int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_imm_reg (int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_load_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int decode_reg_reg (int /*<<< orphan*/ ,struct v810_cmd*) ; 
 int /*<<< orphan*/  r_read_le16 (int /*<<< orphan*/  const*) ; 

int v810_decode_command(const ut8 *instr, int len, struct v810_cmd *cmd) {
	int ret;
	ut16 word1 = 0;
	ut16 word2 = 0;

	word1 = r_read_le16 (instr);
	if (len >= 4) {
		word2 = r_read_le16 (instr + 2);
	}

	switch (OPCODE(word1)) {
	case V810_MOV:
	case V810_ADD:
	case V810_SUB:
	case V810_CMP:
	case V810_SHL:
	case V810_SHR:
	case V810_JMP:
	case V810_SAR:
	case V810_MUL:
	case V810_DIV:
	case V810_MULU:
	case V810_DIVU:
	case V810_OR:
	case V810_AND:
	case V810_NOT:
	case V810_XOR:
		ret = decode_reg_reg (word1, cmd);
		break;
	case V810_MOV_IMM5:
	case V810_ADD_IMM5:
	case V810_SETF:
	case V810_CMP_IMM5:
	case V810_SHL_IMM5:
	case V810_SHR_IMM5:
	case V810_CLI:
	case V810_SAR_IMM5:
	case V810_TRAP:
	case V810_RETI:
	case V810_HALT:
	case V810_LDSR:
	case V810_STSR:
	case V810_SEI:
		ret = decode_imm_reg (word1, cmd);
		break;
	case V810_MOVEA:
	case V810_ADDI:
	case V810_ORI:
	case V810_ANDI:
	case V810_XORI:
	case V810_MOVHI:
		ret = decode_3operands (word1, word2, cmd);
		break;
	case V810_JR:
	case V810_JAL:
		ret = decode_jump (word1, word2, cmd);
		break;
	case V810_LDB:
	case V810_LDH:
	case V810_LDW:
	case V810_STB:
	case V810_STH:
	case V810_STW:
	case V810_INB:
	case V810_INH:
	case V810_CAXI:
	case V810_INW:
	case V810_OUTB:
	case V810_OUTH:
	case V810_OUTW:
		ret = decode_load_store (word1, word2, cmd);
		break;
	case V810_BSTR:
		ret = decode_bit_op (word1, cmd);
		break;
	case V810_EXT:
		ret = decode_extended (word1, word2, cmd);
		break;
	default:
		if ((OPCODE(word1) >> 3) == 0x4) {
			ret = decode_bcond (word1, cmd);
		} else {
			ret = -1;
		}
	}

	if ((ret > 0) && (len < ret)) {
		ret = -1;
	}

	return ret;
}