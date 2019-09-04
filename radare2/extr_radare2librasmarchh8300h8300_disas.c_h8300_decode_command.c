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
typedef  int ut8 ;
struct h8300_cmd {int dummy; } ;

/* Variables and functions */
#define  H8300_ADDB_DIRECT 223 
#define  H8300_ADDS 222 
#define  H8300_ADDW_DIRECT 221 
#define  H8300_ADDX 220 
#define  H8300_ADDX_4BIT 219 
#define  H8300_ADD_4BIT 218 
#define  H8300_AND 217 
#define  H8300_ANDC 216 
#define  H8300_AND_4BIT 215 
#define  H8300_BAND_BIAND 214 
#define  H8300_BCC 213 
#define  H8300_BCLR_IMM2R8 212 
#define  H8300_BCLR_R2ABS8 211 
#define  H8300_BCLR_R2IND16 210 
#define  H8300_BCLR_R2R8 209 
#define  H8300_BCS 208 
#define  H8300_BEQ 207 
#define  H8300_BGE 206 
#define  H8300_BGT 205 
#define  H8300_BHI 204 
#define  H8300_BIAND_IMM2ABS8 203 
#define  H8300_BIAND_IMM2IND16 202 
#define  H8300_BILD_IMM2R8 201 
#define  H8300_BLE 200 
#define  H8300_BLS 199 
#define  H8300_BLT 198 
#define  H8300_BMI 197 
#define  H8300_BNE 196 
#define  H8300_BNOT_1 195 
#define  H8300_BNOT_2 194 
#define  H8300_BOR_BIOR 193 
#define  H8300_BPL 192 
#define  H8300_BRA 191 
#define  H8300_BRN 190 
#define  H8300_BSET_1 189 
#define  H8300_BSET_2 188 
#define  H8300_BSR 187 
#define  H8300_BST_BIST 186 
#define  H8300_BTST 185 
#define  H8300_BTST_R2R8 184 
#define  H8300_BVC 183 
#define  H8300_BVS 182 
#define  H8300_BXOR_BIXOR 181 
#define  H8300_CMP_1 180 
#define  H8300_CMP_2 179 
#define  H8300_CMP_4BIT 178 
#define  H8300_DAA 177 
#define  H8300_DAS 176 
#define  H8300_DEC 175 
#define  H8300_DIVXU 174 
#define  H8300_EEPMOV 173 
#define  H8300_INC 172 
#define  H8300_JMP_1 171 
#define  H8300_JMP_2 170 
#define  H8300_JMP_3 169 
#define  H8300_JSR_1 168 
#define  H8300_JSR_2 167 
#define  H8300_JSR_3 166 
#define  H8300_LDC 165 
#define  H8300_LDC_2 164 
#define  H8300_MOV_1 163 
#define  H8300_MOV_2 162 
#define  H8300_MOV_4BIT 161 
#define  H8300_MOV_4BIT_2 160 
#define  H8300_MOV_4BIT_3 159 
#define  H8300_MOV_ABS162R16 158 
#define  H8300_MOV_DISP162R16 157 
#define  H8300_MOV_IMM162R16 156 
#define  H8300_MOV_IND162R16 155 
#define  H8300_MOV_INDINC162R16 154 
#define  H8300_MOV_R82ABS16 153 
#define  H8300_MOV_R82DISPR16 152 
#define  H8300_MOV_R82IND16 151 
#define  H8300_MOV_R82RDEC16 150 
#define  H8300_MULXU 149 
#define  H8300_NOP 148 
#define  H8300_NOT_NEG 147 
#define  H8300_OR 146 
#define  H8300_ORC 145 
#define  H8300_OR_4BIT 144 
#define  H8300_ROTL 143 
#define  H8300_ROTR 142 
#define  H8300_RTE 141 
#define  H8300_RTS 140 
#define  H8300_SHL 139 
#define  H8300_SHR 138 
#define  H8300_SLEEP 137 
#define  H8300_STC 136 
#define  H8300_SUBS 135 
#define  H8300_SUBW 134 
#define  H8300_SUBX 133 
#define  H8300_SUBX_4BIT 132 
#define  H8300_SUB_1 131 
#define  H8300_XOR 130 
#define  H8300_XORC 129 
#define  H8300_XOR_4BIT 128 
 int decode_abs162r16 (int const*,struct h8300_cmd*) ; 
 int decode_abs2r_short (int const*,struct h8300_cmd*) ; 
 int decode_adds (int const*,struct h8300_cmd*) ; 
 int decode_andc (int const*,struct h8300_cmd*) ; 
 int decode_bsr (int const*,struct h8300_cmd*) ; 
 int decode_daa (int const*,struct h8300_cmd*) ; 
 int decode_disp162r16 (int const*,struct h8300_cmd*) ; 
 int decode_eepmov (int const*,struct h8300_cmd*) ; 
 int decode_imm162r16 (int const*,struct h8300_cmd*) ; 
 int decode_imm2abs8 (int const*,struct h8300_cmd*) ; 
 int decode_imm2ind16 (int const*,struct h8300_cmd*) ; 
 int decode_imm2r8 (int const*,struct h8300_cmd*) ; 
 int decode_imm2r_short (int const*,struct h8300_cmd*) ; 
 int decode_ind162r16 (int const*,struct h8300_cmd*) ; 
 int decode_indinc162r16 (int const*,struct h8300_cmd*) ; 
 int decode_jmp_abs16 (int const*,struct h8300_cmd*) ; 
 int decode_jmp_abs8 (int const*,struct h8300_cmd*) ; 
 int decode_jmp_ind (int const*,struct h8300_cmd*) ; 
 int decode_ldc (int const*,struct h8300_cmd*) ; 
 int decode_nop (int const*,struct h8300_cmd*) ; 
 int decode_r162r16 (int const*,struct h8300_cmd*) ; 
 int decode_r2abs8 (int const*,struct h8300_cmd*) ; 
 int decode_r2imm_short (int const*,struct h8300_cmd*) ; 
 int decode_r2ind16 (int const*,struct h8300_cmd*) ; 
 int decode_r2r8 (int const*,struct h8300_cmd*) ; 
 int decode_r82abs16 (int const*,struct h8300_cmd*) ; 
 int decode_r82dispr16 (int const*,struct h8300_cmd*) ; 
 int decode_r82ind16 (int const*,struct h8300_cmd*) ; 
 int decode_r82r16 (int const*,struct h8300_cmd*) ; 
 int decode_r82rdec16 (int const*,struct h8300_cmd*) ; 
 int decode_subs (int const*,struct h8300_cmd*) ; 

int h8300_decode_command(const ut8 *instr, struct h8300_cmd *cmd)
{
	int ret = 0;

	switch (instr[0] >> 4) {
	case H8300_MOV_4BIT_3:
		ret = decode_r2imm_short(instr, cmd);
		break;
	case H8300_MOV_4BIT_2:
		ret = decode_abs2r_short(instr, cmd);
		break;
	case H8300_AND_4BIT:
	case H8300_ADDX_4BIT:
	case H8300_ADD_4BIT:
	case H8300_CMP_4BIT:
	case H8300_MOV_4BIT:
	case H8300_OR_4BIT:
	case H8300_SUBX_4BIT:
	case H8300_XOR_4BIT:
		ret = decode_imm2r_short(instr, cmd);
		break;
	}

	if (ret) {
		{
			return ret;
		}
	}

	switch (instr[0]) {
	case H8300_ANDC:
		ret = decode_andc(instr, cmd);
		break;
	case H8300_SUBS:
		ret = decode_subs(instr, cmd);
		break;
	case H8300_ADDW_DIRECT:
	case H8300_CMP_2:
		ret = decode_r162r16(instr, cmd);
		break;
	case H8300_ADDS:
		ret = decode_adds(instr, cmd);
		break;
	case H8300_BAND_BIAND:
	case H8300_BCLR_IMM2R8:
	case H8300_BST_BIST:
	case H8300_BTST:
	case H8300_BILD_IMM2R8:
	case H8300_BOR_BIOR:
	case H8300_BXOR_BIXOR:
	case H8300_BNOT_2:
	case H8300_BSET_2:
		ret = decode_imm2r8(instr, cmd);
		break;
	case H8300_AND:
	case H8300_ADDB_DIRECT:
	case H8300_BCLR_R2R8:
	case H8300_SUB_1:
	case H8300_SUBX:
	case H8300_ADDX:
	case H8300_XOR:
	case H8300_BNOT_1:
	case H8300_BSET_1:
	case H8300_CMP_1:
	case H8300_MOV_1:
	case H8300_BTST_R2R8:
		ret = decode_r2r8(instr, cmd);
		break;
	case H8300_BCLR_R2IND16:
		switch(instr[2]) {
		case 0x60:
		case 0x61:
		case 0x62:
			ret = decode_r2ind16(instr, cmd);
			break;
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x67:
		case 0x75:
			ret = decode_imm2ind16(instr, cmd);
			break;
		default:
			ret = -1;
		}
		break;
	case H8300_BCLR_R2ABS8:
		switch (instr[2]) {
		case 0x60:
		case 0x61:
		case 0x62:
			ret = decode_r2abs8(instr, cmd);
			break;
		case 0x67:
		case 0x70:
		case 0x71:
		case 0x72:
			ret = decode_imm2abs8(instr, cmd);
			break;
		default:
			ret = -1;
		}
		break;
	case H8300_BIAND_IMM2IND16:
		ret = decode_imm2ind16(instr, cmd);
		break;
	case H8300_BIAND_IMM2ABS8:
		ret = decode_imm2abs8(instr, cmd);
		break;
	case H8300_BSR:
		ret = decode_bsr(instr, cmd);
		break;
	case H8300_NOP:
		ret = decode_nop(instr, cmd);
		break;
	case H8300_DAA:
	case H8300_DAS:
	case H8300_DEC:
	case H8300_INC:
	case H8300_NOT_NEG:
	case H8300_ROTL:
	case H8300_ROTR:
	case H8300_SHL:
	case H8300_SHR:
		ret = decode_daa(instr, cmd);
		break;
	case H8300_DIVXU:
	case H8300_MULXU:
		ret = decode_r82r16(instr, cmd);
		break;
	case H8300_EEPMOV:
	case H8300_RTS:
	case H8300_RTE:
	case H8300_SLEEP:
		ret = decode_eepmov(instr, cmd);
		break;
	case H8300_JMP_1:
	case H8300_JSR_1:
		ret = decode_jmp_ind(instr, cmd);
		break;
	case H8300_JMP_2:
	case H8300_JSR_2:
		ret = decode_jmp_abs16(instr, cmd);
		break;
	case H8300_JMP_3:
	case H8300_JSR_3:
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
		ret = decode_jmp_abs8(instr, cmd);
		break;
	case H8300_ORC:
	case H8300_LDC:
	case H8300_LDC_2:
	case H8300_STC:
	case H8300_XORC:
		ret = decode_ldc(instr, cmd);
		break;
	case H8300_OR:
		ret = decode_r2r8(instr, cmd);
		break;
	case H8300_MOV_2:
	case H8300_SUBW:
		ret = decode_r162r16(instr, cmd);
		break;
	case H8300_MOV_IMM162R16:
		ret = decode_imm162r16(instr, cmd);
		break;
	case H8300_MOV_IND162R16:
		ret = decode_ind162r16(instr, cmd);
		break;
	case H8300_MOV_DISP162R16:
		ret = decode_disp162r16(instr, cmd);
		break;
	case H8300_MOV_INDINC162R16:
		ret = decode_indinc162r16(instr, cmd);
		break;
	case H8300_MOV_ABS162R16:
		ret = decode_abs162r16(instr, cmd);
		break;
	case H8300_MOV_R82IND16:
		ret = decode_r82ind16(instr, cmd);
		break;
	case H8300_MOV_R82DISPR16:
		ret = decode_r82dispr16(instr, cmd);
		break;
	case H8300_MOV_R82RDEC16:
		ret = decode_r82rdec16(instr, cmd);
		break;
	case H8300_MOV_R82ABS16:
		ret = decode_r82abs16(instr, cmd);
		break;
	default:
		return -1;
	}

	return ret;
}